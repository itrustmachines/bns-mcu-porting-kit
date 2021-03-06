#include <bns-client/core/bns_exit_code.h>

#if defined(LOG_DETAIL)
char* bns_strerror(const int errno) {
  switch (errno) {
    case BNS_OK: return "BNS_OK";
    case BNS_ADDRESS_NULL_ERROR: return "BNS_ADDRESS_NULL_ERROR";
    case BNS_BINARY_LEDGER_INPUT_RESULT_NULL_ERROR:
      return "BNS_BINARY_LEDGER_INPUT_RESULT_NULL_ERROR";
    case BNS_BINARY_LEN_ZERO_ERROR: return "BNS_BINARY_LEN_ZERO_ERROR";
    case BNS_BINARY_INFO_DATA_NULL_ERROR:
      return "BNS_BINARY_INFO_DATA_NULL_ERROR";
    case BNS_BINARY_INFO_FILENAME_NULL_ERROR:
      return "BNS_BINARY_INFO_FILENAME_NULL_ERROR";
    case BNS_BINARY_INFO_NULL_ERROR: return "BNS_BINARY_INFO_NULL_ERROR";
    case BNS_CALLER_ADDRESS_NULL_ERROR: return "BNS_CALLER_ADDRESS_NULL_ERROR";
    case BNS_CHECK_REGISTER_RESPONSE_NULL_ERROR:
      return "BNS_CHECK_REGISTER_RESPONSE_NULL_ERROR";
    case BNS_CHECK_REGISTER_URL_NULL_ERROR:
      return "BNS_CHECK_REGISTER_URL_NULL_ERROR";
    case BNS_CLEARANCE_RECORD_INSTRUCTION_NULL_ERROR:
      return "BNS_CLEARANCE_RECORD_INSTRUCTION_NULL_ERROR";
    case BNS_CLEARANCE_RECORD_NULL_ERROR:
      return "BNS_CLEARANCE_RECORD_NULL_ERROR";
    case BNS_CLIENT_CONFIG_INDEX_VALUE_KEY_NULL_ERROR:
      return "BNS_CLIENT_CONFIG_INDEX_VALUE_KEY_NULL_ERROR";
    case BNS_CLIENT_CONFIG_NODE_URL_NULL_ERROR:
      return "BNS_CLIENT_CONFIG_NODE_URL_NULL_ERROR";
    case BNS_CLIENT_CONFIG_SERVER_URL_NULL_ERROR:
      return "BNS_CLIENT_CONFIG_SERVER_URL_NULL_ERROR";
    case BNS_CLIENT_HTTP_CLIENT_ETH_POST_NULL_ERROR:
      return "BNS_CLIENT_HTTP_CLIENT_ETH_POST_NULL_ERROR";
    case BNS_CLIENT_HTTP_CLIENT_NULL_ERROR:
      return "BNS_CLIENT_HTTP_CLIENT_NULL_ERROR";
    case BNS_CLIENT_HTTP_CLIENT_BNS_GET_NULL_ERROR:
      return "BNS_CLIENT_HTTP_CLIENT_BNS_GET_NULL_ERROR";
    case BNS_CLIENT_HTTP_CLIENT_BNS_POST_MULTI_NULL_ERROR:
      return "BNS_CLIENT_HTTP_CLIENT_BNS_POST_MULTI_NULL_ERROR";
    case BNS_CLIENT_HTTP_CLIENT_BNS_POST_NULL_ERROR:
      return "BNS_CLIENT_HTTP_CLIENT_BNS_POST_NULL_ERROR";
    case BNS_CLIENT_NULL_ERROR: return "BNS_CLIENT_NULL_ERROR";
    case BNS_CLIENT_RECEIPT_DAO_SAVE_NULL_ERROR:
      return "BNS_CLIENT_RECEIPT_DAO_SAVE_NULL_ERROR";
    case BNS_CMD_JSON_NULL_ERROR: return "BNS_CMD_JSON_NULL_ERROR";
    case BNS_CONTRACT_ADDRESS_NULL_ERROR:
      return "BNS_CONTRACT_ADDRESS_NULL_ERROR";
    case BNS_CONTRACT_REQUEST_JSON_NULL_ERROR:
      return "BNS_CONTRACT_REQUEST_JSON_NULL_ERROR";
    case BNS_DONE_CO_NULL_ERROR: return "BNS_DONE_CO_NULL_ERROR";
    case BNS_EMAIL_NULL_ERROR: return "BNS_EMAIL_NULL_ERROR";
    case BNS_ETH_POST_CLEARANCE_RECORD_RESPONSE_NULL_ERROR:
      return "BNS_ETH_POST_CLEARANCE_RECORD_RESPONSE_NULL_ERROR";
    case BNS_GET_DONE_CO_RESPONSE_NULL_ERROR:
      return "BNS_GET_DONE_CO_RESPONSE_NULL_ERROR";
    case BNS_GET_MERKLE_PROOF_RESPONSE_NULL_ERROR:
      return "BNS_GET_MERKLE_PROOF_RESPONSE_NULL_ERROR";
    case BNS_GET_RECEIPT_LOCATOR_RESPONSE_NULL_ERROR:
      return "BNS_GET_RECEIPT_LOCATOR_RESPONSE_NULL_ERROR";
    case BNS_GET_SERVER_INFO_RESPONSE_NULL_ERROR:
      return "BNS_GET_SERVER_INFO_RESPONSE_NULL_ERROR";
    case BNS_GET_SERVER_INFO_URL_NULL_ERROR:
      return "BNS_GET_SERVER_INFO_URL_NULL_ERROR";
    case BNS_INDEX_VALUE_KEY_LEN_OUT_OF_RANGE_ERROR:
      return "BNS_INDEX_VALUE_KEY_LEN_OUT_OF_RANGE_ERROR";
    case BNS_INDEX_VALUE_KEY_NULL_ERROR:
      return "BNS_INDEX_VALUE_KEY_NULL_ERROR";
    case BNS_INDEX_VALUE_NULL_ERROR: return "BNS_INDEX_VALUE_NULL_ERROR";
    case BNS_JSON_NULL_ERROR: return "BNS_JSON_NULL_ERROR";
    case BNS_LEAF_NODE_HASH_NULL_ERROR: return "BNS_LEAF_NODE_HASH_NULL_ERROR";
    case BNS_LEDGER_INPUT_REQUEST_JSON_NULL_ERROR:
      return "BNS_LEDGER_INPUT_REQUEST_JSON_NULL_ERROR";
    case BNS_LEDGER_INPUT_REQUEST_NULL_ERROR:
      return "BNS_LEDGER_INPUT_REQUEST_NULL_ERROR";
    case BNS_LEDGER_INPUT_RESULT_NULL_ERROR:
      return "BNS_LEDGER_INPUT_RESULT_NULL_ERROR";
    case BNS_MERKLE_PROOF_NULL_ERROR: return "BNS_MERKLE_PROOF_NULL_ERROR";
    case BNS_MERKLE_PROOF_TO_SIGN_DATA_NULL_ERROR:
      return "BNS_MERKLE_PROOF_TO_SIGN_DATA_NULL_ERROR";
    case BNS_NODE_URL_NULL_ERROR: return "BNS_NODE_URL_NULL_ERROR";
    case BNS_OUTPUT_JSON_NULL_ERROR: return "BNS_OUTPUT_JSON_NULL_ERROR";
    case BNS_OUTPUT_NULL_ERROR: return "BNS_OUTPUT_NULL_ERROR";
    case BNS_PB_PAIR_NULL_ERROR: return "BNS_PB_PAIR_NULL_ERROR";
    case BNS_POST_LEDGER_INPUT_RESPONSE_NULL_ERROR:
      return "BNS_POST_LEDGER_INPUT_RESPONSE_NULL_ERROR";
    case BNS_POST_REGISTER_RESPONSE_NULL_ERROR:
      return "BNS_POST_REGISTER_RESPONSE_NULL_ERROR";
    case BNS_POST_REGISTER_URL_NULL_ERROR:
      return "BNS_POST_REGISTER_URL_NULL_ERROR";
    case BNS_PRIVATE_KEY_NULL_ERROR: return "BNS_PRIVATE_KEY_NULL_ERROR";
    case BNS_PUBLIC_KEY_NULL_ERROR: return "BNS_PUBLIC_KEY_NULL_ERROR";
    case BNS_RECEIPT_DAO_DELETE_NULL_ERROR:
      return "BNS_RECEIPT_DAO_DELETE_NULL_ERROR";
    case BNS_RECEIPT_DAO_FIND_NULL_ERROR:
      return "BNS_RECEIPT_DAO_FIND_NULL_ERROR";
    case BNS_RECEIPT_DAO_NULL_ERROR: return "BNS_RECEIPT_DAO_NULL_ERROR";
    case BNS_RECEIPT_DAO_SAVE_NULL_ERROR:
      return "BNS_RECEIPT_DAO_SAVE_NULL_ERROR";
    case BNS_RECEIPT_DIGEST_NULL_ERROR: return "BNS_RECEIPT_DIGEST_NULL_ERROR";
    case BNS_RECEIPT_FIRST_PART_TO_SIGN_DATA_NULL_ERROR:
      return "BNS_RECEIPT_FIRST_PART_TO_SIGN_DATA_NULL_ERROR";
    case BNS_RECEIPT_LOCATOR_NULL_ERROR:
      return "BNS_RECEIPT_LOCATOR_NULL_ERROR";
    case BNS_RECEIPT_NULL_ERROR: return "BNS_RECEIPT_NULL_ERROR";
    case BNS_RECEIPT_SECOND_PART_TO_SIGN_DATA_NULL_ERROR:
      return "BNS_RECEIPT_SECOND_PART_TO_SIGN_DATA_NULL_ERROR";
    case BNS_RECEIPT_TO_SIGN_DATA_NULL_ERROR:
      return "BNS_RECEIPT_TO_SIGN_DATA_NULL_ERROR";
    case BNS_REGISTER_NOT_REGISTED: return "BNS_REGISTER_NOT_REGISTED";
    case BNS_REGISTER_REQUEST_JSON_NULL_ERROR:
      return "BNS_REGISTER_REQUEST_JSON_NULL_ERROR";
    case BNS_REGISTER_REQUEST_NULL_ERROR:
      return "BNS_REGISTER_REQUEST_NULL_ERROR";
    case BNS_REGISTER_RESULT_NULL_ERROR:
      return "BNS_REGISTER_RESULT_NULL_ERROR";
    case BNS_RESPONSE_NULL_ERROR: return "BNS_RESPONSE_NULL_ERROR";
    case BNS_SERVER_INFO_NULL_ERROR: return "BNS_SERVER_INFO_NULL_ERROR";
    case BNS_SERVER_INFO_REQUEST_JSON_NULL_ERROR:
      return "BNS_SERVER_INFO_REQUEST_JSON_NULL_ERROR";
    case BNS_SERVER_URL_NULL_ERROR: return "BNS_SERVER_URL_NULL_ERROR";
    case BNS_SERVER_WALLET_ADDRESS_NULL_ERROR:
      return "BNS_SERVER_WALLET_ADDRESS_NULL_ERROR";
    case BNS_SLICE_NULL_ERROR: return "BNS_SLICE_NULL_ERROR";
    case BNS_SLICE_STRING_NULL_ERROR: return "BNS_SLICE_STRING_NULL_ERROR";
    case BNS_VERIFY_RECEIPT_RESULT_NULL_ERROR:
      return "BNS_VERIFY_RECEIPT_RESULT_NULL_ERROR";
    case BNS_JSON_PARSE_ERROR: return "BNS_JSON_PARSE_ERROR";
    case BNS_RESPONSE_BINARY_FILE_URL_PARSE_ERROR:
      return "BNS_RESPONSE_BINARY_FILE_URL_PARSE_ERROR";
    case BNS_RESPONSE_CALLER_ADDRESS_PARSE_ERROR:
      return "BNS_RESPONSE_CALLER_ADDRESS_PARSE_ERROR";
    case BNS_RESPONSE_CLEARANCE_RECORD_PARSE_ERROR:
      return "BNS_RESPONSE_CLEARANCE_RECORD_PARSE_ERROR";
    case BNS_RESPONSE_CMD_PARSE_ERROR: return "BNS_RESPONSE_CMD_PARSE_ERROR";
    case BNS_RESPONSE_CO_PARSE_ERROR: return "BNS_RESPONSE_CO_PARSE_ERROR";
    case BNS_RESPONSE_CONTRACT_ADDRESS_PARSE_ERROR:
      return "BNS_RESPONSE_CONTRACT_ADDRESS_PARSE_ERROR";
    case BNS_RESPONSE_DESCRIPTION_PARSE_ERROR:
      return "BNS_RESPONSE_DESCRIPTION_PARSE_ERROR";
    case BNS_RESPONSE_DONE_CO_PARSE_ERROR:
      return "BNS_RESPONSE_DONE_CO_PARSE_ERROR";
    case BNS_RESPONSE_INDEX_VALUE_PARSE_ERROR:
      return "BNS_RESPONSE_INDEX_VALUE_PARSE_ERROR";
    case BNS_RESPONSE_METADATA_PARSE_ERROR:
      return "BNS_RESPONSE_METADATA_PARSE_ERROR";
    case BNS_RESPONSE_PBPAIR_PARSE_ERROR:
      return "BNS_RESPONSE_PBPAIR_PARSE_ERROR";
    case BNS_RESPONSE_R_PARSE_ERROR: return "BNS_RESPONSE_R_PARSE_ERROR";
    case BNS_RESPONSE_RESULT_PARSE_ERROR:
      return "BNS_RESPONSE_RESULT_PARSE_ERROR";
    case BNS_RESPONSE_S_PARSE_ERROR: return "BNS_RESPONSE_S_PARSE_ERROR";
    case BNS_RESPONSE_SERVER_WALLET_ADDRESS_PARSE_ERROR:
      return "BNS_RESPONSE_SERVER_WALLET_ADDRESS_PARSE_ERROR";
    case BNS_RESPONSE_SIG_CLIENT_PARSE_ERROR:
      return "BNS_RESPONSE_SIG_CLIENT_PARSE_ERROR";
    case BNS_RESPONSE_SIG_SERVER_PARSE_ERROR:
      return "BNS_RESPONSE_SIG_SERVER_PARSE_ERROR";
    case BNS_RESPONSE_SLICE_PARSE_ERROR:
      return "BNS_RESPONSE_SLICE_PARSE_ERROR";
    case BNS_RESPONSE_SN_PARSE_ERROR: return "BNS_RESPONSE_SN_PARSE_ERROR";
    case BNS_RESPONSE_STATUS_PARSE_ERROR:
      return "BNS_RESPONSE_STATUS_PARSE_ERROR";
    case BNS_RESPONSE_TIMESTAMP_PARSE_ERROR:
      return "BNS_RESPONSE_TIMESTAMP_PARSE_ERROR";
    case BNS_RESPONSE_TIMESTAMP_BNS_PARSE_ERROR:
      return "BNS_RESPONSE_TIMESTAMP_BNS_PARSE_ERROR";
    case BNS_RESPONSE_V_PARSE_ERROR: return "BNS_RESPONSE_V_PARSE_ERROR";
    case BNS_BINARY_LEDGER_INPUT_IS_DISABLE_ERROR:
      return "BNS_BINARY_LEDGER_INPUT_IS_DISABLE_ERROR";
    case BNS_CLEARANCE_ORDER_LESS_THAN_OR_EQUAL_TO_ZERO_ERROR:
      return "BNS_CLEARANCE_ORDER_LESS_THAN_OR_EQUAL_TO_ZERO_ERROR";
    case BNS_GET_LEAF_NODE_HASH_OUT_OF_RANGE_ERROR:
      return "BNS_GET_LEAF_NODE_HASH_OUT_OF_RANGE_ERROR";
    case BNS_LEDGER_INPUT_AUTHENTICATION_ERROR:
      return "BNS_LEDGER_INPUT_AUTHENTICATION_ERROR";
    case BNS_LEDGER_INPUT_CLEARANCE_ORDER_ERROR:
      return "BNS_LEDGER_INPUT_CLEARANCE_ORDER_ERROR";
    case BNS_LEDGER_INPUT_CLIENT_SIGNATURE_ERROR:
      return "BNS_LEDGER_INPUT_CLIENT_SIGNATURE_ERROR";
    case BNS_LEDGER_INPUT_CMD_ERROR: return "BNS_LEDGER_INPUT_CMD_ERROR";
    case BNS_LEDGER_INPUT_INDEX_VALUE_ERROR:
      return "BNS_LEDGER_INPUT_INDEX_VALUE_ERROR";
    case BNS_LEDGER_INPUT_TX_COUNT_ERROR:
      return "BNS_LEDGER_INPUT_TX_COUNT_ERROR";
    case BNS_LEDGER_INPUT_WARN: return "BNS_LEDGER_INPUT_WARN";
    case BNS_RECEIPT_FILED_EXCEED_DEFINED_SIZE_ERROR:
      return "BNS_RECEIPT_FILED_EXCEED_DEFINED_SIZE_ERROR";
    case BNS_REGISTER_ERROR: return "BNS_REGISTER_ERROR";
    case BNS_REGISTER_ETHEREUM_ADDRESS_ERROR:
      return "BNS_REGISTER_ETHEREUM_ADDRESS_ERROR";
    case BNS_REGISTER_OUT_OF_REGISTER_COUNT_ERROR:
      return "BNS_REGISTER_OUT_OF_REGISTER_COUNT_ERROR";
    case BNS_REGISTER_PUBLIC_KEY_ERROR: return "BNS_REGISTER_PUBLIC_KEY_ERROR";
    case BNS_REGISTER_SIGNATURE_ERROR: return "BNS_REGISTER_SIGNATURE_ERROR";
    case BNS_REGISTER_TXCOUNT_NOT_ENOUGH_ERROR:
      return "BNS_REGISTER_TXCOUNT_NOT_ENOUGH_ERROR";
    case BNS_RESPONSE_STATUS_ERROR: return "BNS_RESPONSE_STATUS_ERROR";
    case BNS_SLICE_INDEX_NEGATIVE_ERROR:
      return "BNS_SLICE_INDEX_NEGATIVE_ERROR";
    case BNS_SN_NEGATIVE_ERROR: return "BNS_SN_NEGATIVE_ERROR";
    case BNS_RECOVER_PUBLIC_KEY_ERROR: return "BNS_RECOVER_PUBLIC_KEY_ERROR";
    case BNS_SIGN_ERROR: return "BNS_SIGN_ERROR";
    case BNS_VERIFY_SIGNATURE_ERROR: return "BNS_VERIFY_SIGNATURE_ERROR";
    case BNS_CHECK_RECEIPT_IN_PBPAIR_ERROR:
      return "BNS_CHECK_RECEIPT_IN_PBPAIR_ERROR";
    case BNS_CHECK_SLICE_ERROR: return "BNS_CHECK_SLICE_ERROR";
    case BNS_EQUALS_IGNORE_CASE_ERROR: return "BNS_EQUALS_IGNORE_CASE_ERROR";
    case BNS_PB_PAIR_IN_LEAF_NODE_ERROR:
      return "BNS_PB_PAIR_IN_LEAF_NODE_ERROR";
    case BNS_VERIFY_CLEARANCE_ORDER_ERROR:
      return "BNS_VERIFY_CLEARANCE_ORDER_ERROR";
    case BNS_VERIFY_CLEARANCE_RECORD_CLEARANCE_ORDER_ERROR:
      return "BNS_VERIFY_CLEARANCE_RECORD_CLEARANCE_ORDER_ERROR";
    case BNS_VERIFY_CLEARANCE_RECORD_ROOT_HASH_ERROR:
      return "BNS_VERIFY_CLEARANCE_RECORD_ROOT_HASH_ERROR";
    default: return "BNS_UNDEFINED_ERROR";
  }
}
#else
inline bns_exit_code_t bns_strerror(bns_exit_code_t bns_exit_code) {
  return bns_exit_code;
}
#endif  // defined(LOG_DETAIL)
