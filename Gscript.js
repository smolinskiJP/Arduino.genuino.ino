function doGet(e) {

    let id = '1TwqAsZn9qFdYMQ7IoKON4P3vpffS3iMFVGesskxq29o'; 
    let sheetName = 'Iot_Coltec'; 
    var result;

    // e.parameter has received GET parameters, i.e. temperature, humidity, illumination
    if (e.parameter == undefined) {
        result = 'Parameter undefined';
    } else {
        var sheet = SpreadsheetApp.openById(id).getSheetByName(sheetName);
        var newRow = sheet.getLastRow() + 1;  // get row number to be inserted
        var rowData = [];

        // get current time
        rowData[0] = new Date();
        rowData[1] = e.parameter.UniqueID;
        rowData[2] = e.parameter.temperatureC;
        rowData[3] = e.parameter.humidity;
        rowData[4] = e.parameter.temperatureF;

        // 1 x rowData.length cells from (newRow, 1) cell are specified
        var newRange = sheet.getRange(newRow, 1, 1, rowData.length);

        // insert data to the target cells
        newRange.setValues([rowData]);
        result =  'Ok';
    }

    return ContentService.createTextOutput(result);
}
