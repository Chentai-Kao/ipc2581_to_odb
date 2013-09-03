1. 將需要轉檔的 IPC-2581 檔案（此處以"sample.xml"為例）複製到現在這個目錄。
2. 此時，目錄下的檔案應如下圖所示：
   .
   ├── bin
   │   ├── 7z.dll
   │   ├── 7z.exe
   │   ├── ipc2581.exe
   │   ├── libgcc_s_dw2-1.dll
   │   ├── mingwm10.dll
   │   └── QtCore4.dll
   ├── README.txt
   └── sample.xml

3. 打開微軟的命令列視窗。步驟為：
   (1) 打開「開始」主選單
   (2) 點選「執行」
   (3) 鍵入「cmd」，點選「OK」
4. 在命令列中，將路徑移動到現在這個目錄。假設這個目錄目前在桌面，則步驟為：
   (1) 鍵入「cd Desktop\ipc2581」，按Enter。
5. 在命令列中開始轉檔。步驟為：
   (1) 鍵入「bin\ipc2581.exe sample.xml sample.tgz」，按Enter
   (2) 指令包含了三部份，依序為「執行檔名稱」、「來源檔名稱」、「輸出檔名稱」
   (3) 指令中，「輸出檔名稱」可以不填，則預設與來源檔名稱相同（而副檔名為.tgz）
       （例如「bin\ipc2581.exe sample.xml」將會輸出"sample.tgz"）
6. 此時，目錄下的檔案應如下圖所示：（其中的"sample.tgz"即為輸出的ODB++檔案」）
   .
   ├── bin
   │   ├── 7z.dll
   │   ├── 7z.exe
   │   ├── ipc2581.exe
   │   ├── libgcc_s_dw2-1.dll
   │   ├── mingwm10.dll
   │   └── QtCore4.dll
   ├── README.txt
   ├── sample.tgz
   └── sample.xml

7. 用Genesis或其他軟體打開"sample.tgz"驗證
