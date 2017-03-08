import QtQuick 2.0
import NQFramework 1.0
import NQFramework.Api 1.0
import NQFramework.Logger 1.0
import NQViews 1.0
import CustomViews 1.0
import ToyotaCustomControl 1.0
import iauto.fc.proxy 1.0
import iauto.bt.setting 1.0
import iauto.bt.handsfree 1.0
import iauto.system.info 1.0

STP_ConnStatus {
    id: stp_connstatus
    objectName: "STP_ConnStatus"
    width: 800
    height: 480

    // add Model
    FCProxy {
        id: fcListModel
        fcName: "fnctl.bt.setting"
    }

    FCProxy {
        id: fcHandsfreeModel
        fcName: "fnctl.bt.handsfree"
    }

    FCProxy {
        id: fcProxySystem
        fcName: "fnctl.system.info"
    }

    property var btPairedDevInfoModel: fcListModel.getModel("btsettingPairedDeviceInfoModel")
    property var btPropertyModel: fcListModel.getModel("btSettingPropertyModel")
    property var btHandsFreeModel: fcHandsfreeModel.getModel("BtHandsfreePropertyModel")
    property var btSystemModel: fcProxySystem.getModel("btModel")

    // HFP button restriction
    function hfpRestriction(isHfpConnected) {
        if (isHfpConnected) {
            return true
        }
        else {
            return false
        }
    }

    // avp Btn enabled
    function avpBtnEnabled(isSpportAVP, isErrormode, callStatus, isHFPConnected, isSubHFPConnected) {

        // If it is in BT error mode automatic restoration process
        if (isErrormode) {
            return false
        }
        // else if support AVP
        else if (isSpportAVP) {
            // if is not talking,sending,receiving
            if ((isHFPConnected) || (isSubHFPConnected)) {
                if (BtHandsfreeEnum.CallStatus_Idle === callStatus || BtHandsfreeEnum.CallStatus_Disconnected === callStatus) {
                    return true
                }
                else {
                    return false
                }
            }
            else {
                return true
            }
        }
        else {
            return false
        }
    }

    // hfp Btn enabled
    function hfpBtnEnabled(isSpportHFP, isErrormode, callStatus, isHFPConnected, isSubHFPConnected) {

        // If it is in BT error mode automatic restoration process
        if (isErrormode) {
            return false
        }
        // else if support HFP && is not talking,sending,receiving
        else if (isSpportHFP) {
            if ((isHFPConnected) || (isSubHFPConnected)) {
                if (BtHandsfreeEnum.CallStatus_Idle === callStatus || BtHandsfreeEnum.CallStatus_Disconnected === callStatus) {
                    return true
                }
                else {
                    return false
                }
            }
            else {
                return true
            }
        }
        else {
            return false
        }
    }

    // disconnect Btn enabled
    function disconBtnEnabled(isHFPConnectd, isAVPConnected, isErrormode, callStatus, isHFPConnected, isSubHFPConnected) {

        // If it is in BT error mode automatic restoration process
        if (isErrormode) {
            return false
        }
        // else if connect HFP
        else if (isHFPConnectd) {
            // if is not talking,sending,receiving
            if ((isHFPConnected) || (isSubHFPConnected)) {
                if (BtHandsfreeEnum.CallStatus_Idle === callStatus || BtHandsfreeEnum.CallStatus_Disconnected === callStatus) {
                    return true
                }
                else {
                    return false
                }
            }
            else {
                return true
            }
        }
        // else if conenct AVP
        else if (isAVPConnected) {
            // if is not talking,sending,receiving
            if ((isHFPConnected) || (isSubHFPConnected)) {
                if (BtHandsfreeEnum.CallStatus_Idle === callStatus || BtHandsfreeEnum.CallStatus_Disconnected === callStatus) {
                    return true
                }
                else {
                    return false
                }
            }
            else {
                return true
            }
        }
        // else if not connect any
        else {
            return false
        }
    }

    // connectBtn enabled
    function conBtnEnabled(isSpportHFP, isSpportAVP, isHFPConnectd, isAVPConnected, isErrormode, isHFPAvailable, callStatus, isHFPConnected, isSubHFPConnected) {

        // If it is in BT error mode automatic restoration process
        if (isErrormode) {
            return false
        }
        if (isSpportHFP || isSpportAVP) {
            // if HFP or AVP has connected
            if (isHFPConnectd || isAVPConnected) {
                // if two profiles all connected
                if (isHFPConnectd && isAVPConnected) {
                    return false
                }
                // else if only one profile supported and connected
                else if(!isSpportHFP || !isSpportAVP) {
                    return false
                }
                // else if all profiles supported and not conneted
                else {
                    // if HFP is not available and AVP has connected
                    if (!isHFPAvailable && isAVPConnected) {
                        return false
                    }
                    // if is not talking,sending,receiving
                    if ((isHFPConnected) || (isSubHFPConnected)) {
                        if (BtHandsfreeEnum.CallStatus_Idle === callStatus || BtHandsfreeEnum.CallStatus_Disconnected === callStatus) {
                            return true
                        }
                        else {
                            return false
                        }
                    }
                    else {
                        return true
                    }
                }
            }
            else {
                // if is not talking,sending,receiving
                if ((isHFPConnected) || (isSubHFPConnected)) {
                    if (BtHandsfreeEnum.CallStatus_Idle === callStatus || BtHandsfreeEnum.CallStatus_Disconnected === callStatus) {
                        return true
                    }
                    else {
                        return false
                    }
                }
                else {
                    return true
                }
            }
        }
        else {
            return false
        }
    }

    function subPhoneText(isSpportHFP) {
        // if device support HFP
        if (isSpportHFP) {
            return "STR_MM_07_09_03_RES_06"
        }
        // else
        else {
            return ""
        }
    }

    // hfpBtn text
    function hfpText(isSpportHFP, isHFPConnectd) {
        // if support HFP
        if (isSpportHFP) {
            // if not connect HFP
            if (isHFPConnectd) {
                // return "Disconnect as a Phone"
                return "STR_MM_07_09_03_RES_02"
            }
            // else if not connect HFP
            else {
                // return "Connect as a Phone"
                return "STR_MM_07_09_03_RES_03"
            }
        }
        // else if not support HFP
        else {
            return "INVALID_STRID"
        }
    }

    // hfpBtn SpecID
    function hfpSpecID(isSpportHFP, isHFPConnectd) {
        // if support HFP
        if (isSpportHFP) {
            // if not connect HFP
            if (isHFPConnectd) {
                // return "Disconnect as a Phone"
                // return "STR_MM_07_09_03_RES_02"
                return  6297732
            }
            // else if not connect HFP
            else {
                // return "Connect as a Phone"
                // return "STR_MM_07_09_03_RES_03"
                return  6297733
            }
        }
        // else if not support HFP
        else {
            return "INVALID_STRID"
        }
    }
    // avpBtn text
    function avpText(isSpportAVP, isAVPConnected) {
        // if support AVP
        if (isSpportAVP) {
            // if connect AVP
            if (isAVPConnected) {
                // return "Disconnect as an Audio Player"
                return "STR_MM_07_09_03_RES_04"
            }
            // else if not connect AVP
            else {
                // return "Connect as Audio Player"
                return "STR_MM_07_09_03_RES_05"
            }
        }
        // else if not support AVP
        else {
            return ""
        }
    }

    // avpBtn SpecID
    function avpSpecID(isSpportAVP, isAVPConnected) {
        // if support AVP
        if (isSpportAVP) {
            // if connect AVP
            if (isAVPConnected) {
                // return "Disconnect as an Audio Player"
                // return "STR_MM_07_09_03_RES_04"
                return 6297734
            }
            // else if not connect AVP
            else {
                // return "Connect as Audio Player"
                // return "STR_MM_07_09_03_RES_05"
                return 6297735
            }
        }
        // else if not support AVP
        else {
            return ""
        }
    }

    // music icon status
    function musicIcon(isSpportAVP, isAVPConnected) {
        // if support AVP
        if (isSpportAVP) {
            // if connect AVP
            if (isAVPConnected) {
                // music light
//                return "TEX_PNG_BUHIN_03_84_N"
                return "TEX_PNG_BUHIN_03_84_S_LB"

            }
            // if not connect AVP
            else {
                // music dark
//                return "TEX_PNG_BUHIN_03_84_T_LB"
                return "TEX_PNG_BUHIN_03_84_N"
            }
        }
        // else if not support AVP
        else {
            // music disappear
            return ""
        }
    }

    // phone icon status
    function phoneIcon(isSpportHFP, isSpportSPP, isHFPConnectd, isSPPConnected, isTSLConnected, isTSLSupported) {
        // if support HFP
        if (isSpportHFP) {
            // if connect HFP
            if (isHFPConnectd) {
                // if support SSP
                if (isSpportSPP) {
                    // if connect SSP
                    if (isSPPConnected) {
                        // 1.In the case of SPP support for destination transfer (connected)
                        if (isTSLConnected) {
                            // index HFP light and SPP light
//                            return "TEX_PNG_BUHIN_03_60_N_LB_4"
                            return "TEX_PNG_BUHIN_03_60_S_LB_4"
                        }
                        // 2.else
                        else {
                            // index HFP light and SPP light
//                            return "TEX_PNG_BUHIN_03_60_N_LB_7"
                            return "TEX_PNG_BUHIN_03_60_S_LB_7"
                        }
                    }
                    // else if not connect SPP
                    else {
                        // 1.In the case of SPP support for destination transfer (unconnected)
                        if (isTSLSupported) {
                            // index HFP light and SPP dark
//                            return "TEX_PNG_BUHIN_03_60_N_LB_30"
                            return "TEX_PNG_BUHIN_03_60_S_LB_30"
                        }
                        // 2.else
                        else {
                            // display the telephone mark of connection state (SPP connection in Main)
                            // index HFP light and SPP dark
//                            return "TEX_PNG_BUHIN_03_60_N_LB_33"
                            return "TEX_PNG_BUHIN_03_60_S_LB_33"
                        }
                    }
                }
                // else if not support SPP
                else {
                    // index HFP light and SPP disappear
//                    return "TEX_PNG_BUHIN_03_60_N_LB_1"
                    return "TEX_PNG_BUHIN_03_60_S_LB_1"
                }
            }
            // else if not connect HFP
            else {
                // if support SSP
                if (isSpportSPP) {
                    // 1.In the case of SPP support for destination transfer (unconnected)
                    if (isTSLSupported) {
                        // index HFP dark and SPP dark
//                        return "TEX_PNG_BUHIN_03_60_T_LB_4"
                        return "TEX_PNG_BUHIN_03_60_N_LB_4"
                    }
                    // 2.else
                    else {
                        // index HFP dark and SPP dark
//                        return "TEX_PNG_BUHIN_03_60_T_LB_7"
                        return "TEX_PNG_BUHIN_03_60_N_LB_7"
                    }
                }
                // else if not support SPP
                else {
                    // index HFP dark and SPP disappear
//                    return "TEX_PNG_BUHIN_03_60_T_LB_1"
                    return "TEX_PNG_BUHIN_03_60_N_LB_1"
                }
            }
        }
        // else if not support HFP
        else {
            return ""
        }
    }

    function subPhoneBtnEnabled(deviceCount, isSpportHFP) {
        // if device support HFP
        if (isSpportHFP) {
            // if device have add two or more
            if (deviceCount >= 2) {
                return true
            }
            // else if device have add is less than two
            else {
                return false
            }
        }
        // else if device does not support HFP
        else {
            return false
        }
    }

    // add NQCCList
    NQCCList {
        x: 20
        y: 86
        width: 645
        height: 370
        listType: NQCCList.DROP_LIST

        NQItem {
            width: 692
            height: 376
            // Connect
            CC_ListAll_T1_L {
                objectName: "connectBtn"
                restriction: false
                btnEnabled: stp_connstatus.activated?conBtnEnabled(btPairedDevInfoModel.isSpportHFP, btPairedDevInfoModel.isSpportAVP,btPairedDevInfoModel.isHFPConnectd, btPairedDevInfoModel.isAVPConnected, btPropertyModel.isErrormode, btPropertyModel.isHFPAvailable, btHandsFreeModel.callStatus, btPropertyModel.isHFPConnected, btPropertyModel.isSubHFPConnected):false
                x: 72
                width: 612
                height: 62
                textX: 10
                textY: 9
                textW: 595
                textH: 45
                clikBeep: false
                styleId: "F02"
                specID: 6297730
            }

            // Disconnect
            CC_ListAll_T1_L {
                objectName: "disconnectBtn"
                restriction: true
                btnEnabled: stp_connstatus.activated?disconBtnEnabled(btPairedDevInfoModel.isHFPConnectd, btPairedDevInfoModel.isAVPConnected,btPropertyModel.isErrormode, btHandsFreeModel.callStatus, btPropertyModel.isHFPConnected, btPropertyModel.isSubHFPConnected):false
                x: 72
                y: 62
                width: 612
                height: 62
                textX: 10
                textY: 9
                textW: 595
                textH: 45
                styleId: "F02"
                clikBeep: false
                specID: 6297731
            }

            // Connect or Disconnect HFP
            NQItem {
                y: 124
                width: 685
                height: 62
                // left image
                NQImage {
                    objectName: "hfpImg"
                    y: 10
                    width: 40
                    height: 40
                    imageId: stp_connstatus.activated?phoneIcon(btPairedDevInfoModel.isSpportHFP, btPairedDevInfoModel.isSpportSPP, btPairedDevInfoModel.isHFPConnectd, btPairedDevInfoModel.isSPPConnected, btPairedDevInfoModel.isTSLConnected, btPairedDevInfoModel.isTSLSupported):""
                }
                // right button
                CC_ListAll_T1_L {
                    objectName: "hfpBtn"
                    restriction: stp_connstatus.activated?hfpRestriction(btPairedDevInfoModel.isHFPConnectd):false
                    btnEnabled: stp_connstatus.activated?hfpBtnEnabled(btPairedDevInfoModel.isSpportHFP, btPropertyModel.isErrormode, btHandsFreeModel.callStatus, btPropertyModel.isHFPConnected, btPropertyModel.isSubHFPConnected):false
                    x: 72
                    width: 612
                    height: 62
                    textX: 10
                    textY: 9
                    textW: 595
                    textH: 45
                    textId: stp_connstatus.activated?hfpText(btPairedDevInfoModel.isSpportHFP, btPairedDevInfoModel.isHFPConnectd):""
                    styleId: "F02"
                    clikBeep: false
                    specID: stp_connstatus.activated?hfpSpecID(btPairedDevInfoModel.isSpportHFP, btPairedDevInfoModel.isHFPConnectd):""
                }
            }

            // Connect or Disconnect AVP
            NQItem {
                y: 186
                width: 685
                height: 62
                clip: false
                // left image
                NQImage {
                    objectName: "avpImg"
                    y: 10
                    width: 40
                    height: 40
                    imageId: stp_connstatus.activated?musicIcon(btPairedDevInfoModel.isSpportAVP, btPairedDevInfoModel.isAVPConnected):""
                }
                // right button
                CC_ListAll_T1_L {
                    objectName: "avpBtn"
                    restriction: stp_connstatus.activated?hfpRestriction(btPairedDevInfoModel.isAVPConnected):false
                    btnEnabled: stp_connstatus.activated?avpBtnEnabled(btPairedDevInfoModel.isSpportAVP, btPropertyModel.isErrormode, btHandsFreeModel.callStatus, btPropertyModel.isHFPConnected, btPropertyModel.isSubHFPConnected):false
                    x: 72
                    width: 612
                    height: 62
                    textX: 10
                    textY: 9
                    textW: 595
                    textH: 45
                    textId: stp_connstatus.activated?avpText(btPairedDevInfoModel.isSpportAVP, btPairedDevInfoModel.isAVPConnected):""
                    styleId: "F02"
                    clikBeep: false
                    lineType: CC_ListAll_T1_L.TopBottomLines // delete subPhone function
                    specID: stp_connstatus.activated?avpSpecID(btPairedDevInfoModel.isSpportAVP, btPairedDevInfoModel.isAVPConnected):""
                }
            }

            // Set sub phone
            CC_ListAll_T1_L {
                objectName: "subPhoneBtn"
                restriction: true
                visible: false // delete subPhone function
                btnEnabled: stp_connstatus.activated?subPhoneBtnEnabled(deviceCount, btPairedDevInfoModel.isSpportHFP):false
                x: 72
                y: 248
                width: 612
                height: 62
                textX: 10
                textY: 9
                textW: 595
                textH: 45
                textId: stp_connstatus.activated?subPhoneText(btPairedDevInfoModel.isSpportHFP):""
                styleId: "F02"
                clikBeep: false
                lineType: CC_ListAll_T1_L.TopBottomLines
                specID: 6297736
            }

            // device information
            CC_Cmd_T1M1 {
                objectName: "devInfoBtn"
                restriction: true
                x: 68
                y: 312
                width: 294
                height: 60
                textW: 278
                textH: 45
                textX: 8
                textY: 7
                textId: "STR_MM_07_09_03_RES_07"
                styleId: "F16"
                clikBeep: false
                specID: 6297737
                hAlign: NQBtnText.AlignHCenter
            }
        }
    }

    // back button
    CC_Cmd_Back {
        objectName: "backBtn"
        x: 711
        y: 88
        width: 80
        height: 60
        specID: 6297729
    }
}
