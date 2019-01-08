#include "tokentransaction.h"
#include "misc.h"
#include "datamgr.h"

TokenTransaction::TokenTransaction() {
    token_req = false;
}

TokenTransaction::~TokenTransaction() {
}

//ACTBGEWjZH9SZVNVsjRa6X9mUKSwgZkAWz6K:999999497 00000,
//ACTb2BFQQyt4tvfMNEfeG6UjB7jKW7f3Zhz:500 00000,
//2,
//1504061840
void TokenTransaction::trxFromJson(QJsonObject& result_obj) {
    qDebug() << QJsonDocument(result_obj).toJson();
    QJsonObject obj = result_obj.value("result").toObject();
    obj.value("currentPage");
    QJsonArray trxarr = obj.value("dataList").toArray();
    qDebug() << trxarr.size();
    trxvector.totaRecords = obj.value("totalRecords").toInt();
    trxvector.currentPage = obj.value("currentPage").toInt();
    trxvector.totalPage = obj.value("totalPage").toInt();
    trxvector.pageSize = obj.value("pageSize").toInt();;
    trxvector.trx.clear();

	const QString& currencyName = DataMgr::getInstance()->getCurrCurrencyName();
    
    foreach(QJsonValue trxrecords, trxarr) {
        QJsonObject trxobj = trxrecords.toObject();
        
        //fail transfer
		const QString& coinType = trxobj.value("coinType").toString();
        //if (trxobj.value("eventType").toString() != "transfer_to_success") {
		if (currencyName != COMMONASSET && coinType != currencyName)
		{
			trxvector.totaRecords--;
			if (trxvector.totaRecords <= 0)
				trxvector.totaRecords = 0;
			continue;
		}
        
        Transaction trx;
		trx.cointype = coinType;
        trx.from_addr = trxobj.value("from_addr").toString();
        trx.from_acct = trxobj.value("from_acct").toString();
        trx.to_addr = trxobj.value("to_addr").toString();
        trx.to_acct = trxobj.value("to_acct").toString();
        trx.amount = trxobj.value("amount").toString();
        trx.trx_time = trxobj.value("trx_time").toString();
        trx.fee = trxobj.value("fee").toString();
        
		trx.memo = trxobj.value("memo").toString();
		if (trx.memo.startsWith("deposit toACT"))
			trx.memo.clear();

		QString eventParam = trxobj.value("eventParam").toString();
		if (eventParam.isEmpty())
			continue;

		QRegExp rx("(^ACT.*):([0-9]{1,}),(ACT.*):([0-9]{1,}),(.*),(.*)");
		bool ret = rx.exactMatch(eventParam);
		if (ret == false)
			continue;

		QString frombalance = rx.cap(2);
		trx.frombalance = doubleToStr(frombalance.toDouble() / 100000);

		QString tobalance = rx.cap(4);
		trx.tobalance = doubleToStr(tobalance.toDouble() / 100000);

		trxvector.trx.append(trx);
    }
}

void urlAddParam(QString& url, QString& param) {
    url += param + "&";
}

void TokenTransaction::balanceRequestSet(QString& url, QString account_addr, QString contract_id,
        int page_n, int per_page_n, int block_n) {
    QString request = TOKEN_REQ;
    QString per_page = "per_page=" + QString::number(per_page_n);
    QString acct_addr = "acct_address=" + account_addr;
    QString page = "page=" + QString::number(page_n);
    QString asset_type = "contract_id=" + contract_id;
    url = request;
    urlAddParam(url, acct_addr);
    urlAddParam(url, asset_type);
    urlAddParam(url, page);
    urlAddParam(url, per_page);
    //zxlrunqDebug() << url;
}

//int request = false;
void TokenTransaction::showTokenTraction(TrxVector& trxvector) {
    int i = 0;
    
    foreach(Transaction trx, trxvector.trx) {
        i++;
    }
}

void TokenTransaction::httpFinished() {
    pReply->deleteLater();
    pReply = NULL;
    emit tokenTrxRequestEnd();
    token_req = false;
}

void TokenTransaction::httpReadyread() {
	const QByteArray& byteArray = pReply->readAll();
	QJsonDocument doc = QJsonDocument::fromJson(byteArray);
    
    if (doc.isObject()) {
        QJsonObject result = doc.object();
        trxFromJson(result);
    }
}

void TokenTransaction::connectToBlockBrower(QString account_addr, QString contract_id,
        int page_n, int per_page_n, int block_n) {
    if (token_req) {
        return;
    }
    
    QNetworkRequest request;
    QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1_0);
    QString url;
    balanceRequestSet(url, account_addr, contract_id, page_n, per_page_n, block_n);
    trxvector.addr = account_addr;
    trxvector.page = page_n;
    trxvector.contract_id = contract_id;
    //  balanceRequestSet(url, account_addr, asset, page_n, per_page_n);
    
    if (url.startsWith("https")) {
        request.setSslConfiguration(config);
    }
    
    request.setUrl(QUrl(url));
    pReply = netmgr.get(request);
    token_req = true;
    connect(pReply, &QNetworkReply::readyRead, this, &TokenTransaction::httpReadyread);
    connect(pReply, &QNetworkReply::finished, this, &TokenTransaction::httpFinished);
}
