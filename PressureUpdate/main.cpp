#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>
#include <QRandomGenerator>
#include "FhirCRUD.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FhirCRUD test;
    int d, e, dp, sp, hr;

    QJsonObject MedicationRequest;
    MedicationRequest.insert("resourceType", "MedicationRequest");
    MedicationRequest.insert("status", "active");
    MedicationRequest.insert("intent", "order");
    QJsonArray category;
    QJsonObject j0;
    QJsonArray category_coding;
    QJsonObject j1;
    j1.insert("system", "http://terminology.hl7.org/CodeSystem/medicationrequest-category");
    j1.insert("code", "outpatient");
    j1.insert("display", "outpatient");
    category_coding.append(j1);
    j0.insert("coding", category_coding);
    category.append(j0);
    MedicationRequest.insert("category", category);
    QJsonObject medicationCodeableConcept;
    QJsonArray medicationCodeableConcept_coding;
    QJsonObject j2;
    j2.insert("system", "https://www1.nhi.gov.tw/QueryN/Query1.aspx");
    j2.insert("code", "AB55028100");
    j2.insert("display", "IRBETAN F.C. TABLETS 150 MG");
    medicationCodeableConcept_coding.append(j2);
    medicationCodeableConcept.insert("coding", medicationCodeableConcept_coding);
    MedicationRequest.insert("medicationCodeableConcept", medicationCodeableConcept);
    QJsonObject subject;
    subject.insert("reference", "Patient/c6bc36a8-a1d1-4bf2-92b1-47bda16fd39a");    //1351
    MedicationRequest.insert("subject", subject);
    QDateTime DateTime(QDate(2020, 6, 30), QTime(22, 30, 45));
    MedicationRequest.insert("authoredOn", DateTime.toString(Qt::ISODate));
    QJsonArray dosageInstruction;
    QJsonObject j4;
    j4.insert("sequence", 1);
    j4.insert("text", QString::fromLocal8Bit("高血壓藥"));
    QJsonObject timing;
    QJsonObject timing_code;
    QJsonArray timing_code_coding;
    QJsonObject j5;
    j5.insert("system", "http://hl7.org/fhir/ValueSet/timing-abbreviation");
    j5.insert("code", "QD");
    j5.insert("display", "QD");
    timing_code_coding.append(j5);
    timing_code.insert("coding",timing_code_coding);
    timing_code.insert("text", QString::fromLocal8Bit("每日一次"));
    timing.insert("code", timing_code);
    j4.insert("timing", timing);
    QJsonObject route;
    QJsonArray route_coding;
    QJsonObject j6;
    j6.insert("system", QString::fromLocal8Bit("http://mtrsoftware.com.tw/Page_L/用法表.htm"));
    j6.insert("code", "PO");
    j6.insert("display", QString::fromLocal8Bit("口服"));
    route_coding.append(j6);
    route.insert("coding",route_coding);
    j4.insert("route", route);
    dosageInstruction.append(j4);
    MedicationRequest.insert("dosageInstruction", dosageInstruction);
    QJsonObject dispenseRequest;
    QJsonObject validityPeriod;
    validityPeriod.insert("start", "2020-07-01");
    validityPeriod.insert("end", "2020-07-31");
    dispenseRequest.insert("validityPeriod", validityPeriod);
    dispenseRequest.insert("numberOfRepeatsAllowed", 1);
    QJsonObject quantity;
    quantity.insert("value",31);
    quantity.insert("unit","TAB");
    quantity.insert("system","http://terminology.hl7.org/CodeSystem/v3-orderableDrugForm");
    quantity.insert("code","TAB");
    dispenseRequest.insert("quantity",quantity);
    QJsonObject expectedSupplyDuration;
    expectedSupplyDuration.insert("value",31);
    expectedSupplyDuration.insert("unit","days");
    expectedSupplyDuration.insert("system","http://unitsofmeasure.org");
    expectedSupplyDuration.insert("code","d");
    dispenseRequest.insert("expectedSupplyDuration",expectedSupplyDuration);
    MedicationRequest.insert("dispenseRequest", dispenseRequest);
    QJsonDocument doc(MedicationRequest);
    QByteArray jsonData = doc.toJson();

    QString resp = test.Post("https://fhir.dicom.tw/fhir", "MedicationRequest",  jsonData);
    QString MedicationRequest_ID;
    if (resp == "")  qDebug("Failed to post MedicationRequest!");
    else {
        qDebug("Sucess to post MedicationRequest!");
        QByteArray bytes = resp.toUtf8();
        QJsonDocument document = QJsonDocument::fromJson(bytes);
        QJsonObject object = document.object();
        MedicationRequest_ID=object.value("id").toString();
        qDebug()<<MedicationRequest_ID;
    }

    for(int i=1;i<32;i++){
        //上午血壓
        QJsonObject bundle;
        bundle.insert("resourceType", "Observation");
        bundle.insert("status", "final");
        QJsonObject basedOn;
        basedOn.insert("reference", "MedicationRequest/" + MedicationRequest_ID);
        bundle.insert("basedOn", basedOn);
        QJsonArray category;
        QJsonObject j0;
        QJsonArray category_coding;
        QJsonObject j1;
        j1.insert("system", "http://terminology.hl7.org/CodeSystem/observation-category");
        j1.insert("code", "vital-signs");
        j1.insert("display", "Vital Signs");
        category_coding.append(j1);
        j0.insert("coding", category_coding);
        category.append(j0);
        bundle.insert("category", category);
        QJsonObject code;
        QJsonArray code_coding;
        QJsonObject j2;
        j2.insert("system", "http://loinc.org");
        j2.insert("code", "35094-2");
        j2.insert("display", "Blood pressure panel");
        code_coding.append(j2);
        code.insert("coding", code_coding);
        bundle.insert("code", code);
        QJsonObject subject;
        subject.insert("reference", "Patient/c6bc36a8-a1d1-4bf2-92b1-47bda16fd39a");
        bundle.insert("subject", subject);
        d = QRandomGenerator::global()->bounded(1,60);
        e = QRandomGenerator::global()->bounded(1,60);
        QDateTime AM(QDate(2020, 7, i), QTime(8, d, e));
        bundle.insert("effectiveDateTime", AM.toString(Qt::ISODate));
        QJsonArray component;
        QJsonObject j3;
        QJsonObject j3_code;
        QJsonArray j3_code_coding;
        QJsonObject j4;
        j4.insert("system", "http://loinc.org");
        j4.insert("code", "8462-4");
        j4.insert("display", "Distolic blood pressure");
        j3_code_coding.append(j4);
        j3_code.insert("coding", j3_code_coding);
        j3.insert("code", j3_code);
        QJsonObject valueQuantity1;
        dp = QRandomGenerator::global()->bounded(100,160);
        valueQuantity1.insert("value", dp);
        valueQuantity1.insert("unit", "mm[Hg]");
        valueQuantity1.insert("system", "http://unitsofmeasure.org");
        valueQuantity1.insert("code", "mm[Hg]");
        j3.insert("valueQuantity", valueQuantity1);
        component.append(j3);
        QJsonObject j5;
        QJsonObject j5_code;
        QJsonArray j5_code_coding;
        QJsonObject j6;
        j6.insert("system", "http://loinc.org");
        j6.insert("code", "8480-6");
        j6.insert("display", "Systolic blood pressure");
        j5_code_coding.append(j6);
        j5_code.insert("coding", j5_code_coding);
        j5.insert("code", j5_code);
        QJsonObject valueQuantity2;
        sp = QRandomGenerator::global()->bounded(50,100);
        valueQuantity2.insert("value", sp);
        valueQuantity2.insert("unit", "mm[Hg]");
        valueQuantity2.insert("system", "http://unitsofmeasure.org");
        valueQuantity2.insert("code", "mm[Hg]");
        j5.insert("valueQuantity", valueQuantity2);
        component.append(j5);
        bundle.insert("component", component);
        QJsonDocument doc(bundle);
        QByteArray jsonData = doc.toJson();

        resp = test.Post("https://fhir.dicom.tw/fhir", "Observation",  jsonData);
        if (resp == "")  qDebug("Failed to post AM Pressure Observation!");
        else qDebug("Sucess to post AM Pressure Observation!");

        //上午心率
        code_coding = QJsonArray();
        j2.insert("system", "http://loinc.org");
        j2.insert("code", "8867-4");
        j2.insert("display", "Heart rate");
        code_coding.append(j2);
        code.insert("coding", code_coding);
        bundle.insert("code", code);
        d = QRandomGenerator::global()->bounded(1,60);
        e = QRandomGenerator::global()->bounded(1,60);
        AM = QDateTime(QDate(2020, 7, i), QTime(8, d, e));
        bundle.insert("effectiveDateTime", AM.toString(Qt::ISODate));
        bundle.remove("component");
        hr = QRandomGenerator::global()->bounded(55,105);
        valueQuantity1.insert("value", hr);
        valueQuantity1.insert("unit", "{beats}/min");
        valueQuantity1.insert("system", "http://unitsofmeasure.org");
        valueQuantity1.insert("code", "{beats}/min");
        bundle.insert("valueQuantity", valueQuantity1);
        doc = QJsonDocument(bundle);
        jsonData = doc.toJson();

        resp = test.Post("https://fhir.dicom.tw/fhir", "Observation",  jsonData);
        if (resp == "")  qDebug("Failed to post AM HeartRate Observation!");
        else qDebug("Sucess to post AM HeartRate Observation!");

        //下午血壓
        code_coding = QJsonArray();
        j2.insert("system", "http://loinc.org");
        j2.insert("code", "35094-2");
        j2.insert("display", "Blood pressure panel");
        code_coding.append(j2);
        code.insert("coding", code_coding);
        bundle.insert("code", code);
        bundle.remove("valueQuantity");
        d = QRandomGenerator::global()->bounded(1,60);
        e = QRandomGenerator::global()->bounded(1,60);
        QDateTime PM(QDate(2020, 7, i), QTime(16, d, e));
        bundle.insert("effectiveDateTime", PM.toString(Qt::ISODate));
        dp = QRandomGenerator::global()->bounded(100,160);
        component = QJsonArray();
        valueQuantity1.insert("value", dp);
        valueQuantity1.insert("unit", "mm[Hg]");
        valueQuantity1.insert("system", "http://unitsofmeasure.org");
        valueQuantity1.insert("code", "mm[Hg]");
        j3.insert("valueQuantity", valueQuantity1);
        component.append(j3);
        sp = QRandomGenerator::global()->bounded(50,100);
        valueQuantity2.insert("value", sp);
        valueQuantity2.insert("unit", "mm[Hg]");
        valueQuantity2.insert("system", "http://unitsofmeasure.org");
        valueQuantity2.insert("code", "mm[Hg]");
        j5.insert("valueQuantity", valueQuantity2);
        component.append(j5);
        bundle.insert("component", component);
        doc = QJsonDocument(bundle);
        jsonData = doc.toJson();

        resp = test.Post("https://fhir.dicom.tw/fhir", "Observation",  jsonData);
        if (resp == "")  qDebug("Failed to post PM Pressure Observation!");
        else qDebug("Sucess to post PM Pressure Observation!");

        //下午心率
        code_coding = QJsonArray();
        j2.insert("system", "http://loinc.org");
        j2.insert("code", "8867-4");
        j2.insert("display", "Heart rate");
        code_coding.append(j2);
        code.insert("coding", code_coding);
        bundle.insert("code", code);
        d = QRandomGenerator::global()->bounded(1,60);
        e = QRandomGenerator::global()->bounded(1,60);
        PM = QDateTime(QDate(2020, 7, i), QTime(16, d, e));
        bundle.insert("effectiveDateTime", PM.toString(Qt::ISODate));
        bundle.remove("component");
        hr = QRandomGenerator::global()->bounded(55,105);
        valueQuantity1.insert("value", hr);
        valueQuantity1.insert("unit", "{beats}/min");
        valueQuantity1.insert("system", "http://unitsofmeasure.org");
        valueQuantity1.insert("code", "{beats}/min");
        bundle.insert("valueQuantity", valueQuantity1);
        doc = QJsonDocument(bundle);
        jsonData = doc.toJson();

        resp = test.Post("https://fhir.dicom.tw/fhir", "Observation",  jsonData);
        if (resp == "")  qDebug("Failed to post PM HeartRate Observation!");
        else qDebug("Sucess to post PM HeartRate Observation!");

    }

    return a.exec();
}
