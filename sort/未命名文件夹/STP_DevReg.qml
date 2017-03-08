import QtQuick 2.0
import NQFramework 1.0
import NQFramework.Api 1.0
import NQFramework.Logger 1.0
import NQViews 1.0
import CustomViews 1.0
import ToyotaCustomControl 1.0
import ToyotaCustomControl.List 1.0
import iauto.fc.proxy 1.0
import iauto.bt.setting 1.0
import iauto.bt.handsfree 1.0
import iauto.system.info 1.0

STP_DevReg {
    id: stp_devreg
    objectName: "STP_DevReg"
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

     property var btHandsFreeModel: fcHandsfreeModel.getModel("BtHandsfreePropertyModel")
     property var btSystemModel: fcProxySystem.getModel("btModel")
    property var btPropertyModel: fcListModel.getModel("btSettingPropertyModel")

     function isWithLine(isRestriction) {
         return !isRestriction
     }

     function iconChecked(isHFPConnected) {
         if (isHFPConnected) {
             return true
         }
         else {
             return false
         }
     }

     function lineHight(isRestriction) {
         // if isRestriction
         if (isRestriction) {
             return 0
         }
         else {
             return 45
         }
     }

     // music icon visible
     function musicIconVisible(isAVPSupport) {
         // if support AVP
         if (isAVPSupport) {
             return true
         }
         // else if not support AVP
         else {
             return false
         }
     }

     // music icon enabled
     function musicIconEnabled(isAVPConnected, isErrormode, callStatus, isHFPConnected, isSubHFPConnected) {
         // if avp is not connected
         if (!isAVPConnected) {
             // if it is in BT error mode automatic restoration process
             if (isErrormode) {
                 return false
             }
             // else if is not talking,sending,receiving
             else if ((isHFPConnected) || (isSubHFPConnected)) {
                 if (BtHandsfreeEnum.CallStatus_Idle === callStatus || BtHandsfreeEnum.CallStatus_Disconnected === callStatus) {
                     return true
                 }
                 else {
                     return false
                 }
             }
             // else
             else {
                 return true
             }
         }
     }

     // phone icon visible
     function phoneIconVisible(isHFPSupport) {
         // if support HFP
         if (isHFPSupport) {
             return true
         }
         // else if not support HFP
         else {
             return false
         }
     }

     // phone icon enabled
     function phoneIconEnabled(isHFPConnected, isErrormode, callStatus, isHFPConnected, isSubHFPConnected) {

         // if HFP is not connected
         if (!isHFPConnected) {
             // If it is in BT error mode automatic restoration process
             if (isErrormode) {
                 return false
             }
             // else if is not talking,sending,receiving
             else if ((isHFPConnected) || (isSubHFPConnected)) {
                 if (BtHandsfreeEnum.CallStatus_Idle === callStatus || BtHandsfreeEnum.CallStatus_Disconnected === callStatus) {
                     return true
                 }
                 else {
                     return false
                 }
             }
             // else
             else {
                 return true
             }
         }
     }

     // music icon status
     function musicIcon(isAVPSupport, isAVPConnected) {
         // if support AVP
         if (isAVPSupport) {
             // if connect AVP
             if (isAVPConnected) {
                 // music light
//                 return "TEX_PNG_BUHIN_03_84_N"
                 return "TEX_PNG_BUHIN_03_84_S_S, TEX_PNG_BUHIN_03_84_R_S, TEX_PNG_BUHIN_03_84_S_S, TEX_PNG_BUHIN_03_84_T_S"
             }
             // if not connect AVP
             else {
//                 // music dark
//                 return "TEX_PNG_BUHIN_03_84_T_LB"
                 return "TEX_PNG_BUHIN_03_84_N, TEX_PNG_BUHIN_03_84_R_S, TEX_PNG_BUHIN_03_84_S_S, TEX_PNG_BUHIN_03_84_T_S"
             }
         }
         // else if not support AVP
         else {
             // music disappear
             return ""
         }
     }

     // phone icon status
     function phoneIcon(isHFPSupport, isSPPSupport, isHFPConnected, isSPPConnected, isMainPhoneSelected, isSubPhoneSeleted, subDevAddr, isTSLConnected, isTSLSupported) {
         // if support HFP
         if (isHFPSupport) {
             // if connect HFP
             if (isHFPConnected) {
                 // if support SSP
                 if (isSPPSupport) {
                     // if connect as main Phone
                     if (isMainPhoneSelected) {
                         // if connect SPP
                         if (isSPPConnected) {
                             // if have sub phone
                             if (0 !== subDevAddr) {
                                 // 1.In the case of SPP support for destination transfer (connected)
                                 if (isTSLConnected) {
                                     // 1 HFP light and SPP light
//                                     return "TEX_PNG_BUHIN_03_60_N_LB_5"
                                     return "TEX_PNG_BUHIN_03_60_S_S_5, TEX_PNG_BUHIN_03_60_R_S_5, TEX_PNG_BUHIN_03_60_S_S_5, TEX_PNG_BUHIN_03_60_T_S_5"
                                 }
                                 // 2.else
                                 else {
                                     // 1 HFP light and SPP light
//                                     return "TEX_PNG_BUHIN_03_60_N_LB_8"
                                     return "TEX_PNG_BUHIN_03_60_S_S_8, TEX_PNG_BUHIN_03_60_R_S_8, TEX_PNG_BUHIN_03_60_S_S_8, TEX_PNG_BUHIN_03_60_T_S_8"
                                 }
                             }
                             // else if have not sub phone
                             else {
                                 // 1.In the case of SPP support for destination transfer (connected)
                                 if (isTSLConnected) {
                                     // index HFP light and SPP light
//                                     return "TEX_PNG_BUHIN_03_60_N_LB_4"
                                     return "TEX_PNG_BUHIN_03_60_S_S_4, TEX_PNG_BUHIN_03_60_R_S_4, TEX_PNG_BUHIN_03_60_S_S_4, TEX_PNG_BUHIN_03_60_T_S_4"
                                 }
                                 // 2.else
                                 else {
                                     // index HFP light and SPP light
//                                     return "TEX_PNG_BUHIN_03_60_N_LB_7"
                                     return "TEX_PNG_BUHIN_03_60_S_S_7, TEX_PNG_BUHIN_03_60_R_S_7, TEX_PNG_BUHIN_03_60_S_S_7, TEX_PNG_BUHIN_03_60_T_S_7"
                                 }
                             }
                         }
                         // if not connect SPP
                         else {
                             // if have sub phone
                             if (0 !== subDevAddr) {
                                 // 1.In the case of SPP support for destination transfer (unconnected)
                                 if (isTSLSupported) {
                                     // 1 HFP light and SPP dark
//                                     return "TEX_PNG_BUHIN_03_60_N_LB_31"
                                     return "TEX_PNG_BUHIN_03_60_S_S_31, TEX_PNG_BUHIN_03_60_R_S_31, TEX_PNG_BUHIN_03_60_S_S_31, TEX_PNG_BUHIN_03_60_T_S_31"
                                 }
                                 // 2.else
                                 else {
                                     // 1 HFP light and SPP dark
//                                     return "TEX_PNG_BUHIN_03_60_N_LB_34"
                                     return "TEX_PNG_BUHIN_03_60_S_S_34, TEX_PNG_BUHIN_03_60_R_S_34, TEX_PNG_BUHIN_03_60_S_S_34, TEX_PNG_BUHIN_03_60_T_S_34"
                                 }
                             }
                             // else if have not sub phone
                             else {
                                 // 1.In the case of SPP support for destination transfer (unconnected)
                                 if (isTSLSupported) {
                                     // display the smartphone cooperation mark the connection status (SPP connection in Main)
                                     // index HFP light and SPP dark
//                                     return "TEX_PNG_BUHIN_03_60_N_LB_30"
                                     return "TEX_PNG_BUHIN_03_60_S_S_30, TEX_PNG_BUHIN_03_60_R_S_30, TEX_PNG_BUHIN_03_60_S_S_30, TEX_PNG_BUHIN_03_60_T_S_30"
                                 }
                                 // 2.else
                                 else {
                                     // display the telephone mark of connection state (SPP connection in Main)
                                     // index HFP light and SPP dark
//                                     return "TEX_PNG_BUHIN_03_60_N_LB_33"
                                     return "TEX_PNG_BUHIN_03_60_S_S_33, TEX_PNG_BUHIN_03_60_R_S_33, TEX_PNG_BUHIN_03_60_S_S_33, TEX_PNG_BUHIN_03_60_T_S_33"
                                 }
                             }
                         }
                     }
                     // else if connect as sub phone
                     else if (isSubPhoneSeleted){
                         // 1.In the case of SPP support for destination transfer (unconnected)
                         if (isTSLSupported) {
                             // 2 HFP light and SPP dark
//                             return "TEX_PNG_BUHIN_03_60_N_LB_32"
                             return "TEX_PNG_BUHIN_03_60_S_S_32, TEX_PNG_BUHIN_03_60_R_S_32, TEX_PNG_BUHIN_03_60_S_S_32, TEX_PNG_BUHIN_03_60_T_S_32"
                         }
                         // 2.else
                         else {
                             // 2 HFP light and SPP dark
//                             return "TEX_PNG_BUHIN_03_60_N_LB_35"
                             return "TEX_PNG_BUHIN_03_60_S_S_35, TEX_PNG_BUHIN_03_60_R_S_35, TEX_PNG_BUHIN_03_60_S_S_35, TEX_PNG_BUHIN_03_60_T_S_35"
                         }
                     }
                 }
                 // else if not support SPP
                 else {
                     // if connect as main Phone
                     if (isMainPhoneSelected) {
                         // if have sub phone
                         if (0 !== subDevAddr) {
                             // 1 HFP light and SPP disappear
//                             return "TEX_PNG_BUHIN_03_60_N_LB_2"
                             return "TEX_PNG_BUHIN_03_60_S_S_2, TEX_PNG_BUHIN_03_60_R_S_2, TEX_PNG_BUHIN_03_60_S_S_2, TEX_PNG_BUHIN_03_60_T_S_2"
                         }
                         // else if have not sub phone
                         else {
                             // index HFP light and SPP disappear
//                             return "TEX_PNG_BUHIN_03_60_N_LB_1"
                             return "TEX_PNG_BUHIN_03_60_S_S_1, TEX_PNG_BUHIN_03_60_R_S_1, TEX_PNG_BUHIN_03_60_S_S_1, TEX_PNG_BUHIN_03_60_T_S_1"
                         }
                     }
                     // else if connect as sub phone
                     else if (isSubPhoneSeleted) {
                         // 2 HFP light and SPP disappear
//                         return "TEX_PNG_BUHIN_03_60_N_LB_3"
                         return "TEX_PNG_BUHIN_03_60_S_S_3, TEX_PNG_BUHIN_03_60_R_S_3, TEX_PNG_BUHIN_03_60_S_S_3, TEX_PNG_BUHIN_03_60_T_S_3"
                     }
                     // else if not mainPhone or subPhone
                     else {
                         // index HFP light and SPP disappear
//                         return "TEX_PNG_BUHIN_03_60_N_LB_1"
                         return "TEX_PNG_BUHIN_03_60_S_S_1, TEX_PNG_BUHIN_03_60_R_S_1, TEX_PNG_BUHIN_03_60_S_S_1, TEX_PNG_BUHIN_03_60_T_S_1"
                     }
                 }
             }
             // else if not connect as HFP
             else {
                 // if connect as main phone
                 if (isMainPhoneSelected) {
                     // if support SSP
                     if (isSPPSupport) {
                         // if has subPhone
                         if (0 !==subDevAddr) {
                             // 1.In the case of SPP support for destination transfer (unconnected)
                             if (isTSLSupported) {
//                                 // 1 HFP dark and SPP dark
//                                 return "TEX_PNG_BUHIN_03_60_T_LB_5"
                                 return "TEX_PNG_BUHIN_03_60_N_S_5, TEX_PNG_BUHIN_03_60_R_S_5, TEX_PNG_BUHIN_03_60_S_S_5, TEX_PNG_BUHIN_03_60_T_S_5"
                             }
                             // 2.else
                             else {
//                                 // 1 HFP dark and SPP dark
//                                 return "TEX_PNG_BUHIN_03_60_T_LB_8"
                                 return "TEX_PNG_BUHIN_03_60_N_S_8, TEX_PNG_BUHIN_03_60_R_S_8, TEX_PNG_BUHIN_03_60_S_S_8, TEX_PNG_BUHIN_03_60_T_S_8"
                             }
                         }
                         // else if has not subPhone
                         else {
                             // 1.In the case of SPP support for destination transfer (unconnected)
                             if (isTSLSupported) {
//                                 // index HFP dark and SPP dark
//                                 return "TEX_PNG_BUHIN_03_60_T_LB_4"
                                 return "TEX_PNG_BUHIN_03_60_N_S_4, TEX_PNG_BUHIN_03_60_R_S_4, TEX_PNG_BUHIN_03_60_S_S_4, TEX_PNG_BUHIN_03_60_T_S_4"
                             }
                             // 2.else
                             else {
//                                 // index HFP dark and SPP dark
//                                 return "TEX_PNG_BUHIN_03_60_T_LB_7"
                                 return "TEX_PNG_BUHIN_03_60_N_S_7, TEX_PNG_BUHIN_03_60_R_S_7, TEX_PNG_BUHIN_03_60_S_S_7, TEX_PNG_BUHIN_03_60_T_S_7"
                             }
                         }
                     }
                     // else if not support SSP
                     else {
                         // if has subPhone
                         if (0 !== subDevAddr) {
//                             // 1 HFP dark and SPP disappear
//                             return "TEX_PNG_BUHIN_03_60_T_LB_2"
                             return "TEX_PNG_BUHIN_03_60_N_S_2, TEX_PNG_BUHIN_03_60_R_S_2, TEX_PNG_BUHIN_03_60_S_S_2, TEX_PNG_BUHIN_03_60_T_S_2"
                         }
                         // else if has not subPhone
                         else {
//                             // index HFP dark and SPP disappear
//                             return "TEX_PNG_BUHIN_03_60_T_LB_1"
                             return "TEX_PNG_BUHIN_03_60_N_S_1, TEX_PNG_BUHIN_03_60_R_S_1, TEX_PNG_BUHIN_03_60_S_S_1, TEX_PNG_BUHIN_03_60_T_S_1"
                         }
                     }
                 }
                 // if connect as sub phone
                 else if (isSubPhoneSeleted) {
                     // if support SSP
                     if (isSPPSupport) {
                         // In the case of SPP support for destination transfer (unconnected)
                         if (isTSLSupported) {
//                             // 2 HFP dark and SPP dark
//                             return "TEX_PNG_BUHIN_03_60_T_LB_6"
                             return "TEX_PNG_BUHIN_03_60_N_S_6, TEX_PNG_BUHIN_03_60_R_S_6, TEX_PNG_BUHIN_03_60_S_S_6, TEX_PNG_BUHIN_03_60_T_S_6"
                         }
                         // 2.else
                         else {
//                             // 2 HFP dark and SPP dark
//                             return "TEX_PNG_BUHIN_03_60_T_LB_9"
                             return "TEX_PNG_BUHIN_03_60_N_S_9, TEX_PNG_BUHIN_03_60_R_S_9, TEX_PNG_BUHIN_03_60_S_S_9, TEX_PNG_BUHIN_03_60_T_S_9"
                         }
                     }
                     // else if not support SSP
                     else {
//                         // 2 HFP dark and SPP disappear
//                         return "TEX_PNG_BUHIN_03_60_T_LB_3"
                         return "TEX_PNG_BUHIN_03_60_N_S_3, TEX_PNG_BUHIN_03_60_R_S_3, TEX_PNG_BUHIN_03_60_S_S_3, TEX_PNG_BUHIN_03_60_T_S_3"
                     }
                 }
                 // if not connect as main phone or sub phone
                 else {
                     // if support SSP
                     if (isSPPSupport) {
                         // 1.In the case of SPP support for destination transfer (unconnected)
                         if (isTSLSupported) {
//                             // index HFP dark and SPP dark
//                             return "TEX_PNG_BUHIN_03_60_T_LB_4"
                             return "TEX_PNG_BUHIN_03_60_N_S_4, TEX_PNG_BUHIN_03_60_R_S_4, TEX_PNG_BUHIN_03_60_S_S_4, TEX_PNG_BUHIN_03_60_T_S_4"
                         }
                         // 2.else
                         else {
//                             // index HFP dark and SPP dark
//                             return "TEX_PNG_BUHIN_03_60_T_LB_7"
                             return "TEX_PNG_BUHIN_03_60_N_S_7, TEX_PNG_BUHIN_03_60_R_S_7, TEX_PNG_BUHIN_03_60_S_S_7, TEX_PNG_BUHIN_03_60_T_S_7"
                         }
                     }
                     // else if not support SSP
                     else {
//                         // index HFP dark and SPP disappear
//                         return "TEX_PNG_BUHIN_03_60_T_LB_1"
                         return "TEX_PNG_BUHIN_03_60_N_S_1, TEX_PNG_BUHIN_03_60_R_S_1, TEX_PNG_BUHIN_03_60_S_S_1, TEX_PNG_BUHIN_03_60_T_S_1"
                     }
                 }
             }
         }
         // if not support HFP
         else {
             // all disappear
            return ""
         }
     }

     // top line
     NQImage {
         x: 12
         y: 86
         width: 692
         height: 1
         imageId: "TEX_PNG_BUHIN_01_11"
     }

      CC_List {
          x: 12
          y: 86
          width: 764
          height: 373
          sliderHeight: 0
          // model: listmodel    ///< model object
          // slider: false
          clip: false
          model: stp_devreg.activated?fcListModel.getModel("btSettingListModel").pairedlist:""

          delegate: Component {
              NQItem {
                  width: 692
                  height: 62
                  clip: false

                  // Device Name
                  CC_ListAll_T1_L {
                      x: 0
                      y: 0
                      // restriction: true
                      width: 531+161
                      height: 62
                      textX: 171
                      textY: 9
                      textW: 516
                      textH: 45
                      text: stp_devreg.activated?name:""
                      styleId: "F70"
                      clikBeep: false
                      specID: 6297730 + Number(index)
                      // btnEnabled: stp_devreg.activated?isWithLine(isRestriction):false
                      withLine: stp_devreg.activated?isWithLine(isRestriction):false
                      locked: stp_devreg.activated?isRestriction:false
                      onButtonPressed: {
                          stp_devreg.activated?stp_devreg.onDevNameBtnClicked(name, bdAddr, bdAddrStr):"" // "m_name", 0
                      }

                      NQItem {
                          x: -3
                          y: 2
                          width: 164
                          height: 60

                          NQImage {
                              x: 163
                              y: 9
                              width: 1
                              height: stp_devreg.activated?lineHight(isRestriction):0
                              imageId: "TEX_PNG_BUHIN_01_12"
                          }

                          // Hfp Connect
                          // CC_Cmd_M1 {
                          CC_Cmd_T1M1 {
                              // x: 539
                              visible: stp_devreg.activated?phoneIconVisible(isHFPSupport):false
                              btnEnabled: stp_devreg.activated?phoneIconEnabled(Number(isHFPConnected), fcListModel.getModel("btSettingPropertyModel").isErrormode, btHandsFreeModel.callStatus, btPropertyModel.isHFPConnected, btPropertyModel.isSubHFPConnected):false
                              x: 0
                              y: 0
                              width: 76
                              height: 60
                              markX: 18
                              markY: 10
                              markW: 40
                              markH: 40
                              checked: stp_devreg.activated?iconChecked(Number(isHFPConnected)):false
                              locked: stp_devreg.activated?iconChecked(Number(isHFPConnected)):false
                              clikBeep: false
                              // mark: modelImg_1
                              mark: stp_devreg.activated?phoneIcon(Number(isHFPSupport), Number(isSPPSupport), Number(isHFPConnected), Number(isSPPConnected), Number(isMainPhoneSelected), Number(isSubPhoneSeleted), subDevAddr, isTSLConnected, isTSLSupported):""
                              // btnID: index
                              specID: 6297735 + Number(2*index)
                              onButtonPressed: {
                                  stp_devreg.activated?stp_devreg.onHfpBtnClicked(name, bdAddr, bdAddrStr):"" // "m_name", 0
                              }
                          }

                          // Avp Connect
                          // CC_Cmd_M1 {
                          CC_Cmd_T1M1 {
                              visible: stp_devreg.activated?musicIconVisible(Number(isAVPSupport)):false
                              btnEnabled: stp_devreg.activated?musicIconEnabled(Number(isAVPConnected), fcListModel.getModel("btSettingPropertyModel").isErrormode, btHandsFreeModel.callStatus, btPropertyModel.isHFPConnected, btPropertyModel.isSubHFPConnected):false
                              x: 79
                              y: 0
                              width: 76
                              height: 60
                              markX: 18
                              markY: 10
                              markW: 40
                              markH: 40
                              checked: stp_devreg.activated?iconChecked(Number(isAVPConnected)):false
                              locked: stp_devreg.activated?iconChecked(Number(isAVPConnected)):false
                              // mark: modelImg_2
                              mark: stp_devreg.activated?musicIcon(Number(isAVPSupport), Number(isAVPConnected)):"" // isAVPSupport, isAVPConnected
                              // btnID: index
                              clikBeep: false
                              specID: 6297736 + Number(2*index)
                              onButtonPressed: {
                                  stp_devreg.activated?stp_devreg.onAvpBtnClicked(name, bdAddr, bdAddrStr):"" // "m_name", 0
                              }
                          }
                      }
                  }
              } ///< NQItem
          } ///< Component
      } ///< CC_List

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
