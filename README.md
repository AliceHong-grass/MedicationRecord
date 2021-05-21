# MedicationRecord

### https://fhir.dicom.tw/fhir/MedicationRequest?subject=c6bc36a8-a1d1-4bf2-92b1-47bda16fd39a
### 取得該病患的 MedicationRequest。

### https://fhir.dicom.tw/fhir/Observation?subject=c6bc36a8-a1d1-4bf2-92b1-47bda16fd39a&based-on=(MedicationRequestID)&code=35094-2&date=gt2020-07-05T00%3a00%3a01&date=lt2020-07-10T23%3a59%3a59
### 取得該病患基於 MedicationRequest，並且在此時間區間內的血壓紀錄。
##### 血壓的 LONIC Code 為 35094-2。

### https://fhir.dicom.tw/fhir/Observation?subject=c6bc36a8-a1d1-4bf2-92b1-47bda16fd39a&based-on=63627(MedicationRequestID)&code=8867-4&date=gt2020-07-05T00%3a00%3a01&date=lt2020-07-10T23%3a59%3a59
### 取得該病患基於 MedicationRequest，並且在此時間區間內的心率紀錄。
##### 心率的 LONIC Code 為 8867-4。

##### " %3a " 為 " - "。

# 
# 

# 介面操作

* 輸入病患 ID，並按下 getMedicationRequest 的按鍵。
* 選擇 MedicationRequest，並按下該 MedicationRequest 的 confirm 按鍵。
* 選擇想觀看的時間區段，並按下 getObservation 的按鍵。
