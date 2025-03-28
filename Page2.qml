import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 400
    height: 300
    title: "Libuv File Export Demo"

    Column {
        anchors.centerIn: parent
        spacing: 10

        Button {
            text: "Export Signal History"
            onClicked: wifiOptimizer.exportSignalHistoryToFile()
        }

        Button {
            text: "Cancel Export"
            onClicked: wifiOptimizer.cancelExport()
        }
    }

    Connections {
        target: wifiOptimizer
        function onSaveFinished(){
			console.log("✅ 저장 완료")
		}
        function onSaveCancelled(){
			console.log("🛑 저장 취소됨")
		}		
        function onProgressChanged(){
			console.log("📊 저장 진행률:", percent + "%")
		}
    }
}