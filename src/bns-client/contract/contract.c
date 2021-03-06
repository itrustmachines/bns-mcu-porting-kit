#include <bns-client/contract/clearance_record_cache.h>
#include <bns-client/contract/contract.h>
#include <bns-client/util/log.h>
#include <cJSON.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

bns_exit_code_t build_clearance_record_contract_instruction(
    const clearance_order_t clearanceOrder, char** const instruction) {
  LOG_DEBUG(
      "build_clearance_record_contract_instruction() begin, "
      "clearanceOrder=%lld",
      clearanceOrder);
  bns_exit_code_t exitCode = BNS_OK;
  if (clearanceOrder <= 0) {
    exitCode = BNS_CLEARANCE_ORDER_LESS_THAN_OR_EQUAL_TO_ZERO_ERROR;
    goto build_clearance_record_contract_instruction_fail;
  }
  if (!instruction) {
    exitCode = BNS_CLEARANCE_RECORD_INSTRUCTION_NULL_ERROR;
    goto build_clearance_record_contract_instruction_fail;
  }
  if (*instruction) {
    *instruction =
        (char*)realloc(*instruction, sizeof(char) * INSTRUCTION_STR_LEN);
  } else {
    *instruction = (char*)malloc(sizeof(char) * INSTRUCTION_STR_LEN);
  }
  sprintf(*instruction, INSTRUCTION_PREFIX "%064llx", clearanceOrder);
  LOG_DEBUG("build_clearance_record_contract_instruction() end");
  return exitCode;

build_clearance_record_contract_instruction_fail:
  LOG_ERROR(
      "build_clearance_record_contract_instruction() "
      "error, " BNS_EXIT_CODE_PRINT_FORMAT,
      bns_strerror(exitCode));
  return exitCode;
}

bns_exit_code_t build_contract_request_json(const char* const contractAddress,
                                            const char* const instruction,
                                            char** const      requestJson) {
  LOG_DEBUG(
      "build_contract_request_json() begin, contractAddress=%s, instruction=%s",
      contractAddress, instruction);
  bns_exit_code_t exitCode = BNS_OK;
  cJSON*          root     = NULL;
  cJSON*          params   = NULL;
  cJSON*          item     = NULL;
  if (!contractAddress) {
    exitCode = BNS_CONTRACT_ADDRESS_NULL_ERROR;
    goto build_contract_request_json_fail;
  }
  if (!instruction) { exitCode = BNS_CLEARANCE_RECORD_INSTRUCTION_NULL_ERROR; }
  if (!requestJson) {
    exitCode = BNS_CONTRACT_REQUEST_JSON_NULL_ERROR;
    goto build_contract_request_json_fail;
  }

  item   = cJSON_CreateObject();
  params = cJSON_CreateArray();
  root   = cJSON_CreateObject();

  cJSON_AddStringToObject(item, "to", contractAddress);
  cJSON_AddStringToObject(item, "data", instruction);

  cJSON_AddItemToArray(params, item);
  cJSON_AddItemToArray(params, cJSON_CreateString("latest"));

  cJSON_AddStringToObject(root, "jsonrpc", "2.0");
  cJSON_AddStringToObject(root, "method", "eth_call");
  cJSON_AddItemToObject(root, "params", params);
  cJSON_AddNumberToObject(root, "id", 1, 1);

  if (*requestJson) { BNS_FREE(*requestJson); }
  *requestJson = cJSON_PrintUnformatted(root);
  cJSON_Delete(root);
  LOG_DEBUG("build_contract_request_json() end, requestJson=%s", *requestJson);
  return exitCode;

build_contract_request_json_fail:
  cJSON_Delete(root);
  LOG_ERROR("build_contract_request_json() error, " BNS_EXIT_CODE_PRINT_FORMAT,
            bns_strerror(exitCode));
  return exitCode;
}

bns_exit_code_t contract_post_clearance_record(
    const bns_client_t* const bnsClient,
    const clearance_order_t   clearanceOrder,
    clearance_record_t* const clearanceRecord) {
  size_t count = 0;
contract_post_clearance_record_beg:
  LOG_INFO("contract_post_clearance_record() begin, clearanceOrder=%lld",
           clearanceOrder);
  bns_exit_code_t exitCode       = BNS_OK;
  char*           requestMessage = NULL;
  char*           res            = NULL;
  char*           coInstruction  = NULL;
  if (!bnsClient) {
    exitCode = BNS_CLIENT_NULL_ERROR;
    goto contract_post_clearance_record_fail;
  }
  if (!bnsClient->config.nodeUrl) {
    exitCode = BNS_CLIENT_CONFIG_NODE_URL_NULL_ERROR;
    goto contract_post_clearance_record_fail;
  }
  if (!bnsClient->httpClient.eth_post) {
    exitCode = BNS_CLIENT_HTTP_CLIENT_ETH_POST_NULL_ERROR;
    goto contract_post_clearance_record_fail;
  }
  if (clearanceOrder <= 0) {
    exitCode = BNS_CLEARANCE_ORDER_LESS_THAN_OR_EQUAL_TO_ZERO_ERROR;
    goto contract_post_clearance_record_fail;
  }
  if (!clearanceRecord) {
    exitCode = BNS_CLEARANCE_RECORD_NULL_ERROR;
    goto contract_post_clearance_record_fail;
  }
  get_clearance_record_cache(clearanceOrder, clearanceRecord);
  if (clearanceRecord->clearanceOrder != 0) {
    LOG_INFO(
        "contract_post_clearance_record() end, from "
        "cache " CLEARANCE_RECORD_PRINT_FORMAT,
        CLEARANCE_RECORD_TO_PRINT_ARGS(clearanceRecord));
    return exitCode;
  }
  if ((exitCode = build_clearance_record_contract_instruction(
           clearanceOrder, &coInstruction)) != BNS_OK) {
    goto contract_post_clearance_record_fail;
  }
  if ((exitCode = build_contract_request_json(
           bnsClient->bnsServerInfo.contractAddress, coInstruction,
           &requestMessage)) != BNS_OK) {
    goto contract_post_clearance_record_fail;
  }
  BNS_FREE(coInstruction);

  res =
      bnsClient->httpClient.eth_post(bnsClient->config.nodeUrl, requestMessage);
  if (!res) {
    exitCode = BNS_ETH_POST_CLEARANCE_RECORD_RESPONSE_NULL_ERROR;
    goto contract_post_clearance_record_fail;
  }
  BNS_FREE(requestMessage);
  if ((exitCode = check_and_parse_contract_clearance_record_response(
           res, clearanceRecord)) != BNS_OK) {
    goto contract_post_clearance_record_fail;
  }
  BNS_FREE(res);
  set_clearance_record_cache(clearanceRecord);
  LOG_INFO(
      "contract_post_clearance_record() end, " CLEARANCE_RECORD_PRINT_FORMAT,
      CLEARANCE_RECORD_TO_PRINT_ARGS(clearanceRecord));
  return exitCode;

contract_post_clearance_record_fail:
  if (coInstruction) { BNS_FREE(coInstruction); }
  if (requestMessage) { BNS_FREE(requestMessage); }
  if (res) { BNS_FREE(res); }
  LOG_ERROR(
      "contract_post_clearance_record() error, " BNS_EXIT_CODE_PRINT_FORMAT,
      bns_strerror(exitCode));
  if (bnsClient && bnsClient->maxRetryCount) {
    if (count++ < *bnsClient->maxRetryCount) {
      LOG_DEBUG("contract_post_clearance_record() retry, count=%ld", count);
      if (bnsClient->retryDelaySec) { sleep(*bnsClient->retryDelaySec); }
      goto contract_post_clearance_record_beg;
    }
  }
  return exitCode;
}

bns_exit_code_t check_and_parse_contract_clearance_record_response(
    const char* const res, clearance_record_t* const clearanceRecord) {
  LOG_DEBUG("check_and_parse_contract_clearance_record_response() begin");
  bns_exit_code_t exitCode = BNS_OK;
  cJSON*          root     = NULL;
  cJSON*          item;
  if (!clearanceRecord) {
    exitCode = BNS_CLEARANCE_RECORD_NULL_ERROR;
    goto check_contract_clearance_record_response_fail;
  }
  root = cJSON_Parse(res);
  item = cJSON_GetObjectItem(root, "error");
  if (item) {
    exitCode = BNS_RESPONSE_STATUS_ERROR;
    goto check_contract_clearance_record_response_fail;
  }
  item = cJSON_GetObjectItem(root, "result");
  if (!cJSON_IsString(item)) {
    exitCode = BNS_RESPONSE_CLEARANCE_RECORD_PARSE_ERROR;
    goto check_contract_clearance_record_response_fail;
  }
  strncpy(clearanceRecord->rootHash, item->valuestring + 2 + 64, 64);
  strncpy(clearanceRecord->chainHash, item->valuestring + 2 + 64 * 2, 64);
  clearanceRecord->clearanceOrder = 0;
  for (int i = 2; i < 2 + 64; i++) {
    clearanceRecord->clearanceOrder *= 16;
    if (isdigit(item->valuestring[i])) {
      clearanceRecord->clearanceOrder += item->valuestring[i] - '0';
    } else if (isalpha(item->valuestring[i])) {
      clearanceRecord->clearanceOrder +=
          tolower(item->valuestring[i]) - 'a' + 10;
    } else {
      exitCode = BNS_RESPONSE_CLEARANCE_RECORD_PARSE_ERROR;
      goto check_contract_clearance_record_response_fail;
    }
  }

  cJSON_Delete(root);
  LOG_DEBUG(
      "check_and_parse_contract_clearance_record_response() "
      "end" CLEARANCE_RECORD_PRINT_FORMAT,
      CLEARANCE_RECORD_TO_PRINT_ARGS(clearanceRecord));
  return exitCode;

check_contract_clearance_record_response_fail:
  cJSON_Delete(root);
  LOG_ERROR(
      "check_and_parse_contract_clearance_record_response() "
      "error, " BNS_EXIT_CODE_PRINT_FORMAT,
      bns_strerror(exitCode));
  return exitCode;
}
