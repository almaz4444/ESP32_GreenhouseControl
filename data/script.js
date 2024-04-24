var gateway = `ws://${window.location.hostname}/ws`;
var websocket;

window.addEventListener('load', onload);

var chartT = new Highcharts.Chart({
    chart: { renderTo: 'chart-temperature' },
    title: { text: 'Температура' },
    data: {
        csvURL: "/temperature_datas.csv",
        enablePolling: true,
        dataRefreshRate: 1
    },
    plotOptions: {
        line: {
            animation: false,
            dataLabels: { enabled: true }
        },
        series: {
            color: '#059e8a'
        }
    },
    xAxis: {
        type: 'datetime',
        dateTimeLabelFormats: { second: '%H:%M:%S' }
    },
    yAxis: {
        title: { text: 'Температура (°C)' }
    },
    credits: {
        enabled: false
    },
    tooltip: {
        shared: true,
        useHTML: true,
        headerFormat: '<table><tr><th colspan="2">{point.key}</th></tr>',
        pointFormat: '<tr><td style="color: {series.color}">{series.name} ' + '</td>' + '<td style="text-align: right"><b>{point.y} °C</b></td></tr>',
    },
});

var chartH = new Highcharts.Chart({
    chart:{ renderTo: 'chart-humidity' },
    title: { text: 'Влажность воздуха' },
    data: {
        csvURL: "/humidity_datas.csv",
        enablePolling: true,
        dataRefreshRate: 1
    },
    plotOptions: {
        line: {
            animation: false,
            dataLabels: { enabled: true }
        }
    },
    xAxis: {
        type: 'datetime',
        dateTimeLabelFormats: { second: '%H:%M:%S' },
    },
    yAxis: {
        title: { text: 'Влажность (%)' }
    },
    credits: { enabled: false },
    tooltip: {
        shared: true,
        useHTML: true,
        headerFormat: '<table><tr><th colspan="2">{point.key}</th></tr>',
        pointFormat: '<tr><td style="color: {series.color}">{series.name} ' + '</td>' + '<td style="text-align: right"><b>{point.y} %</b></td></tr>',
    },
});

var chartP = new Highcharts.Chart({
    chart:{ renderTo: 'chart-pressure' },
    title: { text: 'Давление' },
    data: {
        csvURL: "/pressure_datas.csv",
        enablePolling: true,
        dataRefreshRate: 1
    },
    plotOptions: {
        line: {
            animation: false,
            dataLabels: { enabled: true }
        },
        series: { color: '#18009c' }
    },
    xAxis: {
        type: 'datetime',
        dateTimeLabelFormats: { second: '%H:%M:%S' }
    },
    yAxis: {
        title: { text: 'Давление (hPa)' }
    },
    credits: { enabled: false },
    tooltip: {
        shared: true,
        useHTML: true,
        headerFormat: '<table><tr><th colspan="2">{point.key}</th></tr>',
        pointFormat: '<tr><td style="color: {series.color}">{series.name} ' + '</td>' + '<td style="text-align: right"><b>{point.y} hPa</b></td></tr>',
    },
});

// var graphLoaded = false;

// function loadGraph() {
//     var xhttp = new XMLHttpRequest();
//     xhttp.onreadystatechange = function() {
//         if (this.readyState == 4 && this.status == 200) {
//             var sensorsDatas = this.responseText.split("\n").slice(-100);

//             for (const sensorsData of sensorsDatas) {
//                 if (sensorsData) {
//                     var sensorsDataJSON = JSON.parse(sensorsData);
//                     var keys = Object.keys(sensorsDataJSON);
                    
//                     for (const key of keys){
//                         if (key != "time") {
//                             var x = parseInt(sensorsDataJSON["time"]);
//                             var y = parseFloat(sensorsDataJSON[key]);

//                             console.log(x, y)
                            
//                             var chart, series_index;

//                             if (key == "temperature_bmp") { chart = chartT; series_index = 0; }
//                             else if (key == "temperature_dht") { chart = chartT; series_index = 1; }
//                             else if (key == "humidity") { chart = chartH; series_index = 0; }
//                             else if (key == "pressure") { chart = chartP; series_index = 0; }
                            
//                             if(chart.series[series_index].data.length > 100) chart.series[series_index].addPoint([x, y], true, true, true);
//                             else chart.series[series_index].addPoint([x, y], true, false, true);
//                         }
//                     }
//                 }
//             }
//         }
//         graphLoaded = true;
//     };
//     xhttp.open("GET", "/get_sensors_datas", true);
//     xhttp.send();
// }

// function onload(event) {
//     // loadGraph();
//     initWebSocket();
// }

// function getReadings(){
//     websocket.send("getReadings");
// }

// function initWebSocket() {
//     websocket = new WebSocket(gateway);
//     // websocket.onopen = onOpen;
//     websocket.onclose = onClose;
//     websocket.onmessage = onMessage;
// }

// function onOpen(event) {
//     getReadings();
// }

// function onClose(event) {
//     setTimeout(initWebSocket, 2000);
// }

// function sleep(ms) {
//     return new Promise(resolve => setTimeout(resolve, ms));
// }

// function onMessage(event) {
//     loadGraph();
//     while (!graphLoaded) {
//         console.log(graphLoaded);
//         sleep(1);
//     }

//     var sensorsData = JSON.parse(event.data);
//     var keys = Object.keys(sensorsData);
    
//     for (const key of keys){
//         if (key != "time") {
//             var x = parseInt(sensorsData["time"]);
//             var y = parseFloat(sensorsData[key]);
            
//             var chart, series_index;

//             if (key == "temperature_bmp") { chart = chartT; series_index = 0; }
//             else if (key == "temperature_dht") { chart = chartT; series_index = 1; }
//             else if (key == "humidity") { chart = chartH; series_index = 0; }
//             else if (key == "pressure") { chart = chartP; series_index = 0; }
            
//             if(chart.series[series_index].data.length > 100) chart.series[series_index].addPoint([x, y], true, true, true);
//             else chart.series[series_index].addPoint([x, y], true, false, true);
//         }
//     }
// }