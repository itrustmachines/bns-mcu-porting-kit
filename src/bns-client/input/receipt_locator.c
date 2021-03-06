#include <bns-client/input/receipt_locator.h>
#include <bns-client/util/log.h>
#include <bns-client/util/numeric_util.h>
#include <cJSON.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void build_get_receipt_locator_url(char**            url,
                                   const char* const serverUrl,
                                   const char* const indexValueKey) {
  if (!url) { return; }
  size_t size = strlen(serverUrl) + strlen(LEDGER_RECEIPT_LOCATOR_PATH) +
                strlen(indexValueKey);
  *url = (char*)malloc(sizeof(char) * (size + 1));
  if (*url) {
    sprintf(*url, "%s%s%s", serverUrl, LEDGER_RECEIPT_LOCATOR_PATH,
            indexValueKey);
  }
}

bns_exit_code_t bns_get_receipt_locator(
    const bns_client_t* const bnsClient,
    receipt_locator_t* const  receiptLocator) {
  size_t count = 0;
bns_get_receipt_locator_beg:
  LOG_DEBUG("bns_get_receipt_locator() begin");
  bns_exit_code_t exitCode;
  char*           url = NULL;
  char*           res = NULL;

  if (!bnsClient) {
    exitCode = BNS_CLIENT_NULL_ERROR;
    goto bns_get_receipt_locator_fail;
  }
  if (!bnsClient->config.serverUrl) {
    exitCode = BNS_CLIENT_CONFIG_SERVER_URL_NULL_ERROR;
    goto bns_get_receipt_locator_fail;
  }
  if (!bnsClient->config.indexValueKey) {
    exitCode = BNS_CLIENT_CONFIG_INDEX_VALUE_KEY_NULL_ERROR;
    goto bns_get_receipt_locator_fail;
  }
  if (!bnsClient->httpClient.get) {
    exitCode = BNS_CLIENT_HTTP_CLIENT_BNS_GET_NULL_ERROR;
    goto bns_get_receipt_locator_fail;
  }
  if (!receiptLocator) {
    exitCode = BNS_RECEIPT_LOCATOR_NULL_ERROR;
    goto bns_get_receipt_locator_fail;
  }

  build_get_receipt_locator_url(&url, bnsClient->config.serverUrl,
                                bnsClient->config.indexValueKey);

  res = bnsClient->httpClient.get(url);
  if (!res) {
    exitCode = BNS_GET_RECEIPT_LOCATOR_RESPONSE_NULL_ERROR;
    goto bns_get_receipt_locator_fail;
  }

  BNS_FREE(url);

  if ((exitCode = check_and_parse_receipt_locator_response(
           res, bnsClient->config.indexValueKey, receiptLocator)) != BNS_OK) {
    goto bns_get_receipt_locator_fail;
  }

  BNS_FREE(res);

  LOG_DEBUG("bns_get_receipt_locator() end, " RECEIPT_LOCATOR_PRINT_FORMAT,
            RECEIPT_LOCATOR_TO_PRINT_ARGS(receiptLocator));
  return exitCode;

bns_get_receipt_locator_fail:
  if (url) { BNS_FREE(url); }
  if (res) { BNS_FREE(res); }
  receipt_locator_free(receiptLocator);
  LOG_ERROR("bns_get_receipt_locator() error, " BNS_EXIT_CODE_PRINT_FORMAT,
            bns_strerror(exitCode));
  if (bnsClient && bnsClient->maxRetryCount) {
    if (count++ < *bnsClient->maxRetryCount) {
      LOG_DEBUG("bns_get_receipt_locator() retry, count=%ld", count);
      if (bnsClient->retryDelaySec) { sleep(*bnsClient->retryDelaySec); }
      goto bns_get_receipt_locator_beg;
    }
  }
  return exitCode;
}

bns_exit_code_t check_and_parse_receipt_locator_response(
    const char* const        res,
    const char* const        indexValueKey,
    receipt_locator_t* const receiptLocator) {
  LOG_DEBUG("check_receipt_locator_response() begin, res=%s", res);
  bns_exit_code_t exitCode;
  cJSON*          root = NULL;
  if (!indexValueKey) {
    exitCode = BNS_INDEX_VALUE_KEY_NULL_ERROR;
    goto check_receipt_locator_response_fail;
  }
  if (!receiptLocator) {
    exitCode = BNS_RECEIPT_LOCATOR_NULL_ERROR;
    goto check_receipt_locator_response_fail;
  }

  root = cJSON_Parse(res);

  cJSON* temp = cJSON_GetObjectItem(root, "status");
  if (!cJSON_IsString(temp)) {
    exitCode = BNS_RESPONSE_STATUS_PARSE_ERROR;
    goto check_receipt_locator_response_fail;
  }
  if (strcmp(BNS_STATUS_OK, temp->valuestring) != 0) {
    exitCode = BNS_RESPONSE_STATUS_ERROR;
    goto check_receipt_locator_response_fail;
  }
  cJSON_DetachItemViaPointer(root, temp);
  cJSON_Delete(temp);

  temp = cJSON_GetObjectItem(root, "clearanceOrder");

  if (!cJSON_IsNumber(temp)) {
    exitCode = BNS_RESPONSE_CO_PARSE_ERROR;
    goto check_receipt_locator_response_fail;
  }
  clearance_order_t clearanceOrder = temp->valueint;
  cJSON_DetachItemViaPointer(root, temp);
  cJSON_Delete(temp);

  temp = cJSON_GetObjectItem(root, "sn");
  if (!cJSON_IsNumber(temp)) {
    exitCode = BNS_RESPONSE_SN_PARSE_ERROR;
    goto check_receipt_locator_response_fail;
  }
  sn_t sn = temp->valueint;
  cJSON_DetachItemViaPointer(root, temp);
  cJSON_Delete(temp);

  if ((exitCode = build_receipt_locator(indexValueKey, clearanceOrder, sn,
                                        receiptLocator)) != BNS_OK) {
    goto check_receipt_locator_response_fail;
  }

  cJSON_Delete(root);
  LOG_DEBUG("check_receipt_locator_response() end");
  return exitCode;

check_receipt_locator_response_fail:
  cJSON_Delete(root);
  LOG_ERROR(
      "check_receipt_locator_response() error, " BNS_EXIT_CODE_PRINT_FORMAT,
      bns_strerror(exitCode));
  return exitCode;
}

bns_exit_code_t build_receipt_locator(const char* const        indexValueKey,
                                      const clearance_order_t  clearanceOrder,
                                      const sn_t               sn,
                                      receipt_locator_t* const receiptLocator) {
  bns_exit_code_t exitCode = BNS_OK;
  if (!indexValueKey) {
    exitCode = BNS_INDEX_VALUE_KEY_NULL_ERROR;
    goto build_receipt_locator_fail;
  }
  if (clearanceOrder <= 0) {
    exitCode = BNS_CLEARANCE_ORDER_LESS_THAN_OR_EQUAL_TO_ZERO_ERROR;
    goto build_receipt_locator_fail;
  }
  if (sn < 0) {
    exitCode = BNS_SN_NEGATIVE_ERROR;
    goto build_receipt_locator_fail;
  }
  if (!receiptLocator) {
    exitCode = BNS_RECEIPT_LOCATOR_NULL_ERROR;
    goto build_receipt_locator_fail;
  }
  receiptLocator->clearanceOrder = clearanceOrder;
  size_t size                    = strlen(indexValueKey) + 2 + bns_digits(sn);
  receiptLocator->indexValue     = (char*)malloc(sizeof(char) * (size + 1));
  sprintf(receiptLocator->indexValue, "%s_R%lld", indexValueKey, sn);
  LOG_DEBUG("build_receipt_locator() end" RECEIPT_LOCATOR_PRINT_FORMAT,
            RECEIPT_LOCATOR_TO_PRINT_ARGS(receiptLocator));
  return exitCode;

build_receipt_locator_fail:
  LOG_ERROR("build_receipt_locator() error, " BNS_EXIT_CODE_PRINT_FORMAT,
            bns_strerror(exitCode));
  return exitCode;
}

void receipt_locator_free(receipt_locator_t* const receiptLocator) {
  if (receiptLocator) {
    if (receiptLocator->indexValue) { BNS_FREE(receiptLocator->indexValue); }
  }
}
