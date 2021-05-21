#include "FhirCRUD.h"

QString FhirCRUD::replyFinished(QNetworkReply *reply){
	QString response;
	QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	if (statusCode.isValid())	qDebug() << "status code=" << statusCode.toInt();
	QNetworkReply::NetworkError err = reply->error();
	if (err != QNetworkReply::NoError) 	qDebug() << "Failed: " << reply->errorString();
	else  response = reply->readAll();
	return response;
}

QString FhirCRUD::Get(QString url, QString resource, QString id) {
	QNetworkRequest request;
	QNetworkAccessManager* naManager = new QNetworkAccessManager(this);
	request.setUrl(QUrl(url + "/" + resource + "?_id=" + id));
	QNetworkReply* reply = naManager->get(request);
	QEventLoop eventLoop1;
	connect(naManager, &QNetworkAccessManager::finished, &eventLoop1, &QEventLoop::quit);
	eventLoop1.exec();
	return replyFinished(reply);
}

QString FhirCRUD::Post(QString url, QString resource, QByteArray json) {
	QNetworkRequest request;
	request.setUrl(QUrl(url + "/" + resource));
	QNetworkAccessManager* naManager = new QNetworkAccessManager(this);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(json.size()));
	QNetworkReply* reply = naManager->post(request, json);
	QEventLoop eventLoop1;
	connect(naManager, &QNetworkAccessManager::finished, &eventLoop1, &QEventLoop::quit);
	eventLoop1.exec();
	return replyFinished(reply);
}

QString FhirCRUD::Put(QString url, QString resource, QString id, QByteArray json) {
	QNetworkRequest request;
	request.setUrl(QUrl(url + "/" + resource + "/" + id));
	QNetworkAccessManager* naManager = new QNetworkAccessManager(this);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/fhir+json");
	request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(json.size()));
	QNetworkReply* reply = naManager->put(request, json);
	QEventLoop eventLoop1;
	connect(naManager, &QNetworkAccessManager::finished, &eventLoop1, &QEventLoop::quit);
	eventLoop1.exec();
	return replyFinished(reply);
}

QString FhirCRUD::Delete(QString url, QString resource, QString id) {
	QNetworkRequest request;
	request.setUrl(QUrl(url + "/" + resource + "/" + id));
	QString token = "eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJodHRwczovL29hdXRoLmRpY29tLm9yZy50dyIsInN1YiI6Ik1JLVRXMjAyMOW3peS9nOWwj-e1hCIsImF1ZCI6IjE1MC4xMTcuMTIxLjY3IiwiaWF0IjoxNjAyODE3MjEzLCJleHAiOjE2MDY2NjU2MDAsImp0aSI6Ijk1N2Y2MTA2LTdjZWMtNGMwMS04OTk2LWFhNDVlNmQ4NzIwMSJ9.jCKom90GnMkjXJe9uyjjLZzFOtR0PNajCfLechxuc36RgGEaNUvcmG9HhePrvzdrBjU6af7Kk-U8-xgljNcdPJZYlW0xvAZ1aTX4EvfECTFLJNux3Xcglm4B9Ujwj4CRoVyG1fdkQoX2jt0Wkj6akn4Wo3QD7MFr_sc8hKP4TQ8UNZT4m2MM8dSlc9eLd42ArYGGteQ8pc7VbowoDIgbDLGMWmc-pO481u0BB535JtY4Vw1b0f1y-bhc6tRzOUnMjF2DjOdvZeqOpcFhV6q_lIcm4OazNEhP3YdVXIGTLJHq6BvKjj23lsd2vj1wcNDi4opkAwet765FRV-Tydh6JQ";
	const QString header = QStringLiteral("Bearer %1").arg(token);
	request.setRawHeader(QByteArray("Authorization"), header.toUtf8());
	QNetworkAccessManager* naManager = new QNetworkAccessManager(this);
	QNetworkReply* reply = naManager->deleteResource(request);
	QEventLoop eventLoop1;
	connect(naManager, &QNetworkAccessManager::finished, &eventLoop1, &QEventLoop::quit);
	eventLoop1.exec();
	return replyFinished(reply);
}

QString FhirCRUD::Search(QString url, QString resource, QString condition) {
	QString all;
	QNetworkRequest request;
	request.setUrl(QUrl(url + "/" + resource + "?" + condition));
	QNetworkAccessManager* naManager = new QNetworkAccessManager(this);
	QNetworkReply* reply = naManager->get(request);
	QEventLoop eventLoop1;
	connect(naManager, &QNetworkAccessManager::finished, &eventLoop1, &QEventLoop::quit);
	eventLoop1.exec();
	QString response = replyFinished(reply);
	QByteArray bytes = response.toUtf8();
	QJsonDocument document = QJsonDocument::fromJson(bytes);
	QJsonObject object = document.object();
	QString relat = object.value("link").toArray().at(1).toObject().value("relation").toString();
	QString Url = object.value("link").toArray().at(1).toObject().value("url").toString();
	if (relat == nullptr)	all += response;
	else	all += response + ",";
	while (relat == QString::fromLocal8Bit("next"))
	{
		request.setUrl(QUrl(Url));
		QNetworkAccessManager* Manager = new QNetworkAccessManager(this);
		QNetworkReply* rep = Manager->get(request);
		QEventLoop eventLoop2;
		connect(Manager, &QNetworkAccessManager::finished, &eventLoop2, &QEventLoop::quit);
		eventLoop2.exec();
		QString resp = replyFinished(rep);

		QByteArray byt = resp.toUtf8();
		QJsonDocument doc = QJsonDocument::fromJson(byt);
		QJsonObject obj = doc.object();
		relat = obj.value("link").toArray().at(1).toObject().value("relation").toString();
		Url = obj.value("link").toArray().at(1).toObject().value("url").toString();

		if (relat == QString::fromLocal8Bit("previous"))	all += resp;
		else	all += resp + ",";
	}
	
	return "{\n \"ALL\":[\n" + all + "]}";
}