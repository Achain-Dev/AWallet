#include "wallet.h"


Walllet::Walllet() {
}

Walllet::~Walllet() {
}

void Walllet::create(QString& name, QString& password) {
	clearPrefixAndParams();
    setCommand(QString("wallet_create"));
	insertParam(param_type::string_param, name);
	insertParam(param_type::string_param, password);
	sendCommand();
}

void Walllet::getInfo() {
	clearPrefixAndParams();
    setCommand(QString("wallet_get_info"));
	sendCommand();
}

void Walllet::close() {
	clearPrefixAndParams();
    setCommand(QString("wallet_close"));
	sendCommand();
}

void Walllet::open(const QString& name) {
	clearPrefixAndParams();
    setCommand(QString("wallet_open"));
	insertParam(param_type::string_param, name);
	sendCommand();
}

void Walllet::unlock(int time_out, QString& password) {
	clearPrefixAndParams();
    setCommand(QString("wallet_unlock"));
	QString param_value = QString::number(time_out);
	insertParam(param_type::string_param, param_value);
	insertParam(param_type::string_param, password);
	sendCommand();
}

void Walllet::importPrivateKey(QString& wif_key_to_import, QString& account_name, bool create_account, bool rescan_blockchain) {
	clearPrefixAndParams();
    setCommand(QString("wallet_import_private_key"));
	QString param_value = wif_key_to_import;
	insertParam(param_type::string_param, param_value);
	param_value = account_name;
	insertParam(param_type::string_param, param_value);
	param_value = create_account ? "1" : "0";
	insertParam(param_type::bool_param, param_value);
	param_value = rescan_blockchain ? "1" : "0";
	insertParam(param_type::bool_param, param_value);
	sendCommand();
}

void Walllet::importRegisterPrivateKey(QString& wif_key_to_import, QString& account_name, bool create_account, bool rescan_blockchain) {
	clearPrefixAndParams();
    setCommand(QString("wallet_import_private_key"));
    addSpeicalPrefix(QString("register_"));
	QString param_value = wif_key_to_import;
	insertParam(param_type::string_param, param_value);
	param_value = account_name;
	insertParam(param_type::string_param, param_value);
	param_value = create_account ? "1" : "0";
	insertParam(param_type::bool_param, param_value);
	param_value = rescan_blockchain ? "1" : "0";
	insertParam(param_type::bool_param, param_value);
	sendCommand();
}

void Walllet::backupCreate(QString& path_file) {
	clearPrefixAndParams();
    setCommand(QString("wallet_backup_create"));
	QString param_value = path_file;
	insertParam(param_type::string_param, param_value);
	sendCommand();
}

void Walllet::backupRestore(QString& path_file, QString& name, QString& password) {
	clearPrefixAndParams();
    setCommand(QString("wallet_backup_restore"));
	QString param_value = path_file;
	insertParam(param_type::string_param, param_value);
	param_value = name;
	insertParam(param_type::string_param, param_value);
	param_value = password;
	insertParam(param_type::string_param, param_value);
	sendCommand();
}

void Walllet::setAutomaticBackups(bool enable) {
	clearPrefixAndParams();
    setCommand(QString("wallet_set_automatic_backups"));
	QString param_value = enable ? "1" : "0";
	insertParam(param_type::bool_param, param_value);
	sendCommand();
}

void Walllet::setTransactionExpirationTime(int time) {
	clearPrefixAndParams();
    setCommand(QString("wallet_set_transaction_expiration_time"));
	QString param_value = QString::number(time);
	insertParam(param_type::integer_param, param_value);
	sendCommand();
}

void Walllet::accountTransactionHistory(QString& account_name, QString& asset_name) {
	clearPrefixAndParams();
    setCommand(QString("wallet_account_transaction_history"));
	QString param_value = account_name;
	insertParam(param_type::string_param, param_value);
	param_value = asset_name;
	insertParam(param_type::string_param, param_value);
	sendCommand();
}

void Walllet::transactionHistorySplite(QString& user, 
	QString& asset_name, int limit, int trx_type) {
	clearPrefixAndParams();
    setCommand(QString("wallet_transaction_history_splite"));
	QString param_value = user;
	insertParam(param_type::string_param, param_value);
	param_value = asset_name;
	insertParam(param_type::string_param, param_value);
	param_value = QString::number(limit);
	insertParam(param_type::integer_param, param_value);
	param_value = QString::number(trx_type);
	insertParam(param_type::integer_param, param_value);
	sendCommand();
}

void Walllet::transactionHistorySpliteWithId(QString& user, 
	QString& asset_name, int limit, int trx_type) {
	clearPrefixAndParams();
	setCommand(QString("wallet_transaction_history_splite"));
	QString param_value = user;
	insertParam(param_type::string_param, param_value);
	param_value = asset_name;
	insertParam(param_type::string_param, param_value);
	param_value = QString::number(limit);
	insertParam(param_type::integer_param, param_value);
	param_value = QString::number(trx_type);
	insertParam(param_type::integer_param, param_value);

	QString post("_");
	post += user;
	addSepcialPostfix(post);

	sendCommand();
}

void Walllet::getPendingTransactionErrors(QString& path_file) {
	clearPrefixAndParams();
    setCommand(QString("wallet_get_pending_transaction_errors"));
	QString param_value = path_file;
	insertParam(param_type::string_param, param_value);
	sendCommand();
}

void Walllet::changePassphrase(QString& old_password, QString& new_password) {
	clearPrefixAndParams();
    setCommand(QString("wallet_change_passphrase"));
	QString param_value = old_password;
	insertParam(param_type::string_param, param_value);
	param_value = new_password;
	insertParam(param_type::string_param, param_value);
	sendCommand();
}

void Walllet::checkPassphrase(const QString& password) {
	clearPrefixAndParams();
    setCommand(QString("wallet_check_passphrase"));
	QString param_value = password;
	insertParam(param_type::string_param, param_value);
	sendCommand();
}

void Walllet::checkAddress(QString& address) {
	clearPrefixAndParams();
    setCommand(QString("wallet_check_address"));
	QString param_value = address;
	insertParam(param_type::string_param, param_value);
	sendCommand();
}

void Walllet::accountCreate(QString& account_name) {
	clearPrefixAndParams();
    setCommand(QString("wallet_account_create"));
	QString param_value = account_name;
	insertParam(param_type::string_param, param_value);
	sendCommand();
}

void Walllet::accountSetApproval(QString& account_name, int approval) {
	clearPrefixAndParams();
    setCommand(QString("wallet_account_set_approval"));
	QString param_value = account_name;
	insertParam(param_type::string_param, param_value);
	param_value = QString::number(approval);
	insertParam(param_type::integer_param, param_value);
	sendCommand();
}

void Walllet::transferToAddress(QString& amount_to_transfer, 
	QString& asset_symbol, QString& from_account_name, 
	QString& to_address, QString& memo_message, QString& strategy) {
	clearPrefixAndParams();
    setCommand(QString("wallet_transfer_to_address"));
	QString param_value = amount_to_transfer;
	insertParam(param_type::string_param, param_value);
	param_value = asset_symbol;
	insertParam(param_type::string_param, param_value);
	param_value = from_account_name;
	insertParam(param_type::string_param, param_value);
	param_value = to_address;
	insertParam(param_type::string_param, param_value);
	param_value = memo_message;
	insertParam(param_type::string_param, param_value);
	param_value = strategy;
	insertParam(param_type::string_param, param_value);
	sendCommand();
}

void Walllet::transferToAddressWithId(QString unique_trx_id,
	QString& amount_to_transfer, QString& asset_symbol,
	QString& from_account_name, QString& to_address,
	QString& memo_message, QString& strategy) {
	clearPrefixAndParams();
	addSepcialPostfix(QString("wallet_transfer_to_address"));
	setCommand(QString("wallet_transfer_to_address"));
	QString param_value = amount_to_transfer;
	insertParam(param_type::string_param, param_value);
	param_value = asset_symbol;
	insertParam(param_type::string_param, param_value);
	param_value = from_account_name;
	insertParam(param_type::string_param, param_value);
	param_value = to_address;
	insertParam(param_type::string_param, param_value);
	param_value = memo_message;
	insertParam(param_type::string_param, param_value);
	param_value = strategy;
	insertParam(param_type::string_param, param_value);

	QString post("_");
	post += unique_trx_id;
	addSepcialPostfix(post);

	sendCommand();
}

void Walllet::transferToPublicAccount(QString& amount_to_transfer, 
	QString& asset_symbol, QString& from_account_name, 
	QString& to_account_name, QString& memo_message, QString& strategy) {
	clearPrefixAndParams();
    setCommand(QString("wallet_transfer_to_public_account"));
	QString param_value = amount_to_transfer;
	insertParam(param_type::string_param, param_value);
	param_value = asset_symbol;
	insertParam(param_type::string_param, param_value);
	param_value = from_account_name;
	insertParam(param_type::string_param, param_value);
	param_value = to_account_name;
	insertParam(param_type::string_param, param_value);
	param_value = memo_message;
	insertParam(param_type::string_param, param_value);
	param_value = strategy;
	insertParam(param_type::string_param, param_value);
	sendCommand();
}

void Walllet::transferToPublicAccountWithId(QString unique_trx_id,
	QString& amount_to_transfer, QString& asset_symbol, 
	QString& from_account_name, QString& to_account_name, 
	QString& memo_message, QString& strategy) {
	clearPrefixAndParams();
    setCommand(QString("wallet_transfer_to_public_account"));
	QString param_value = amount_to_transfer;
	insertParam(param_type::string_param, param_value);
	param_value = asset_symbol;
	insertParam(param_type::string_param, param_value);
	param_value = from_account_name;
	insertParam(param_type::string_param, param_value);
	param_value = to_account_name;
	insertParam(param_type::string_param, param_value);
	param_value = memo_message;
	insertParam(param_type::string_param, param_value);
	param_value = strategy;
	insertParam(param_type::string_param, param_value);

	QString post("_");
	post += unique_trx_id;
	addSepcialPostfix(post);

	sendCommand();
}

void Walllet::rescanBlockchain() {
	clearPrefixAndParams();
    setCommand(QString("wallet_rescan_blockchain"));
	sendCommand();
}

void Walllet::cancelScan() {
	clearPrefixAndParams();
    setCommand(QString("wallet_cancel_scan"));
	sendCommand();
}

void Walllet::getTransaction(QString& transaction_id_prefix) {
	clearPrefixAndParams();
    setCommand(QString("wallet_get_transaction"));
	QString param_value = transaction_id_prefix;
	insertParam(param_type::string_param, param_value);
	sendCommand();
}

void Walllet::accountRegiste(QString& account_name, 
	QString& pay_from_account, QString& public_data, 
	int delegate_pay_rate, QString& account_type) {
	clearPrefixAndParams();
    setCommand(QString("wallet_account_register"));
	QString param_value = account_name;
	insertParam(param_type::string_param, param_value);
	param_value = pay_from_account;
	insertParam(param_type::string_param, param_value);
	param_value = public_data;
	insertParam(param_type::string_param, param_value);
	param_value = QString::number(delegate_pay_rate);
	insertParam(param_type::integer_param, param_value);
	param_value = account_type;
	insertParam(param_type::string_param, param_value);
	sendCommand();
}

void Walllet::listAccounts() {
	clearPrefixAndParams();
    setCommand(QString("wallet_list_accounts"));
	sendCommand();
}

void Walllet::listUnregisteredAccounts() {
	clearPrefixAndParams();
    setCommand(QString("wallet_list_unregistered_accounts"));
	sendCommand();
}

void Walllet::listMyAddress() {
	clearPrefixAndParams();
    setCommand(QString("wallet_list_my_addresses"));
	sendCommand();
}

void Walllet::listMyAccounts() {
	clearPrefixAndParams();
    setCommand(QString("wallet_list_my_accounts"));
	sendCommand();
}

void Walllet::getAccountPublicAddress(QString& account) {
	clearPrefixAndParams();
    setCommand(QString("wallet_get_account_public_address"));
	QString param_value = account;
	insertParam(param_type::string_param, param_value);
	sendCommand();
}

void Walllet::accountRename(QString& current_name, QString& new_name) {
	clearPrefixAndParams();
    setCommand(QString("wallet_account_rename"));
	QString param_value = current_name;
	insertParam(param_type::string_param, param_value);
	param_value = new_name;
	insertParam(param_type::string_param, param_value);
	sendCommand();
}

void Walllet::accountBalance(QString& account_name) {
	clearPrefixAndParams();
    setCommand(QString("wallet_account_balance"));
	QString param_value = account_name;
	insertParam(param_type::string_param, param_value);
	sendCommand();
}

void Walllet::accountBalanceIds(QString& account_name) {
	clearPrefixAndParams();
    setCommand(QString("wallet_account_balance_ids"));
	QString param_value = account_name;
	insertParam(param_type::string_param, param_value);
	sendCommand();
}
void Walllet::delegateWithdrawPay(QString& delegate_name, 
	QString& to_account_name, QString& amount_to_withdraw) {
	clearPrefixAndParams();
    setCommand(QString("wallet_delegate_withdraw_pay"));
	QString param_value = delegate_name;
	insertParam(param_type::string_param, param_value);
	param_value = to_account_name;
	insertParam(param_type::string_param, param_value);
	param_value = amount_to_withdraw;
	insertParam(param_type::string_param, param_value);
	sendCommand();
}

void Walllet::delegatePayBalanceQuery(QString& account_name) {
	clearPrefixAndParams();
    setCommand(QString("wallet_delegate_pay_balance_query"));
	QString param_value = account_name;
	insertParam(param_type::string_param, param_value);
	sendCommand();
}

void Walllet::getDelegateStatus(QString& account_name) {
	clearPrefixAndParams();
    setCommand(QString("wallet_get_delegate_statue"));
	QString param_value = account_name;
	insertParam(param_type::string_param, param_value);
	sendCommand();
}

void Walllet::accountDelete(QString& account_name) {
	clearPrefixAndParams();
    setCommand(QString("wallet_account_delete"));
	QString param_value = account_name;
	insertParam(param_type::string_param, param_value);
	sendCommand();
}

void Walllet::setTransactionFee(QString& trx_fee) {
	clearPrefixAndParams();
    setCommand(QString("wallet_set_transaction_fee"));
	QString param_value = trx_fee;
	insertParam(param_type::string_param, param_value);
	sendCommand();
}

void Walllet::getTransactionFee(QString& asset_name) {
	clearPrefixAndParams();
    setCommand(QString("wallet_get_transaction_fee"));
	QString param_value = asset_name;
	insertParam(param_type::string_param, param_value);
	sendCommand();
}

void Walllet::setTransactionScanning(bool enable) {
	clearPrefixAndParams();
    setCommand(QString("wallet_set_transaction_scanning"));
	QString param_value = enable ? "1" : "0";
	insertParam(param_type::bool_param, param_value);
	sendCommand();
}

void Walllet::dumpPrivateKey(QString& addr) {
	clearPrefixAndParams();
    setCommand(QString("wallet_dump_private_key"));
	QString param_value = addr;
	insertParam(param_type::string_param, param_value);
	sendCommand();
}

void Walllet::delegateSetBlockProduction(QString& name, bool enable) {
	clearPrefixAndParams();
    setCommand(QString("wallet_delegate_set_block_production"));
	QString param_value = name;
	insertParam(param_type::string_param, param_value);
	param_value = enable ? "1" : "0";
	insertParam(param_type::bool_param, param_value);
	sendCommand();
}

void Walllet::dumpAccountPrivateKey(QString& name, int type) {
	clearPrefixAndParams();
    setCommand(QString("wallet_dump_account_private_key"));
	QString param_value = name;
	insertParam(param_type::string_param, param_value);
	param_value = QString::number(type);
	insertParam(param_type::integer_param, param_value);
	sendCommand();
}

void Walllet::accountUpdateRegistration(QString& account_name,
	QString& pay_from_account, QString& public_data, 
	int delegate_pay_rate, QString& account_type) {
	clearPrefixAndParams();
	setCommand(QString("wallet_account_update_registration"));
	QString param_value = account_name;
	insertParam(param_type::string_param, param_value);
	param_value = pay_from_account;
	insertParam(param_type::string_param, param_value);
	param_value = public_data;
	insertParam(param_type::string_param, param_value);
	param_value = QString::number(delegate_pay_rate);
	insertParam(param_type::integer_param, param_value);
	param_value = account_type;
	insertParam(param_type::string_param, param_value);
	sendCommand();
}
