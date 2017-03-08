/**
 * Copyright @ 2014 - 2016 Suntec Software(Shanghai) Co., Ltd.
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are NOT permitted except as agreed by
 * Suntec Software(Shanghai) Co., Ltd.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */

/*---------------------------------------------------------------------------*/
// Include headers
/*---------------------------------------------------------------------------*/
#include "ngbase/NGLog.h"

#include "STP_DevReg.h"
#include "BtSetupCommon.h"

#include "ngframeworkbase/NGAPI.h"

// share data
#include "ngapp/AppAPI.h"
#include "UI_BaseDef.h"
#include "UI_ShareDataDef.h"
#include "UI_AppContextDef.h"
#include "UI_TransitionNameID.h"

#include "UICommonInfo/UICommonInfoFunc.h"
#include "UICommonInfo/UICommonInfoPhone.h"

#include "qmlframework/NQAPI.h"
#include "qmlframework/NQText.h"
#include <qmlframework/NQResourceManager.h>
#include "qmlframework/NQCCList.h"

#include "UICC/CC_StaticListModel.h"
#include "UICC/CC_Cmd_Back.h"
#include "UICC/CC_ListAll_T1_L.h"

#include "fnctl/base/FCProxyBase.h"
#include "fnctl/BtSetting/BtSettingInterfaceDef.h"
#include "fnctl/BtSetting/BtSettingPairedListModel.h"
#include "fnctl/BtSetting/BtSettingPropertyModel.h"
#include "fnctl/BtSetting/BtSettingMainDeviceInfoModel.h"


#include "fnctl/BtHandsfree/BtHandsfreePropertyModel.h"
#include "fnctl/BtHandsfree/BtHandsfreeDef.h"

/*---------------------------------------------------------------------------*/
// Constant definition
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
// Variable definition
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
// Public functions: Basic functions
/*---------------------------------------------------------------------------*/
// Constructor
/*
 * unitTest's usecase
 * UT: whether the function execution is completed
*/
STP_DevReg::STP_DevReg(QQuickItem *parent)
    : UIMainScreenBase(parent)
    , m_backBtn(NULL)
    , m_dropList(NULL)
    , m_addr(0)
    , m_otherAddr(0)
    , m_devName("")
    , m_addrStr("")
    , m_profFlag(0)
    , m_error(false)
    , m_callStatus(0)
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<XX-XX-XX-XX # 0.000>
    */

}

// Destructor
/*
 * unitTest's usecase
 * UT: whether the function execution is completed
*/
STP_DevReg::~STP_DevReg()
{
    /*
     * ReferenceSequence:<SequenceName # Version>
     * @datalist:<XX-XX-XX-XX # X.XXX>|<YY-YY-YY-YY # Y.YYY>
     */

}

// onCreate
/*
 * unitTest's usecase
 * UT: whether the function execution is completed
*/
void STP_DevReg::onCreate()
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<XX-XX-XX-XX # 0.000>
    */

    NGLogDebug(LogTag_BT_Setup, "View STP_DevReg was created.");

    /*
     * To do something before UIMainScreenBase::onCreate() called.
     */
    m_dropList = this->findChild<NQCCList*>("cc_list");
    NGLogDebug(LogTag_BT_Setup,  "[%s] m_dropList is %p", __PRETTY_FUNCTION__, m_dropList);

    // get m_backBtn
    m_backBtn = this->findChild<CC_Cmd_Back*>("backBtn");
    NGLogDebug(LogTag_BT_Setup,  "[%s] m_backBtn is %p", __PRETTY_FUNCTION__, m_backBtn);
    if (NULL != m_backBtn) {
        NGLogDebug(LogTag_BT_Setup,  "[%s] find child m_backBtn", __PRETTY_FUNCTION__);
        // connect(m_backBtn, SIGNAL(buttonClicked(int)), this, SLOT(onBackBtnClicked()))
        connect(m_backBtn, SIGNAL(buttonPressed(int)), this, SLOT(onBackBtnClicked()));
    }

    UIMainScreenBase::onCreate();
}

// onPreActive
/*
 * unitTest's usecase
 * UT: whether the function execution is completed
*/
void STP_DevReg::onPreActive()
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<XX-XX-XX-XX # 0.000>
    */

    NGLogDebug(LogTag_BT_Setup, "View STP_DevReg will be actived.");

    /*
     * To do something before UIMainScreenBase::onPreActive() called.
     */

    NGLogDebug(LogTag_BT_Setup, "[%s] BtSetupCommonInst: %p", __PRETTY_FUNCTION__, BtSetupCommonInst);
    if (NULL != BtSetupCommonInst) {
        BtSetupCommonInst->notifyTitleChanged("STR_MM_07_09_02_RES_00", BtSetupCommon::ContectType_StringId);
    }

    // get devName and bdaddr from common
    NGLogDebug(LogTag_BT_Setup, "[%s] BtSetupCommonInst is: %p", __PRETTY_FUNCTION__, BtSetupCommonInst);
    if (NULL != BtSetupCommonInst) {
        m_devName = BtSetupCommonInst->deviceName();
        NGLogDebug(LogTag_BT_Setup, "[%s] m_devName is: %s", __PRETTY_FUNCTION__, m_devName.toStdString().c_str());
        m_addr = BtSetupCommonInst->bluetoothAddr();
        NGLogDebug(LogTag_BT_Setup, "[%s] m_addr is: %llu", __PRETTY_FUNCTION__, m_addr);
    }

    // init m_error
    NGLogDebug(LogTag_BT_Setup, "[%s] BtSetupCommonInst is: %p", __PRETTY_FUNCTION__, BtSetupCommonInst);
    if (NULL != BtSettingPropertyModelInst) {
        m_error = BtSettingPropertyModelInst->isErrormode();
        NGLogDebug(LogTag_BT_Setup, "[%s] m_error is: %d", __PRETTY_FUNCTION__, m_error);
    }

    // init m_callStatus
    NGLogDebug(LogTag_BT_Setup, "[%s] BtHandsfreePropertyModelInst is: %p", __PRETTY_FUNCTION__, BtHandsfreePropertyModelInst);
    if (NULL != BtHandsfreePropertyModelInst) {
        m_callStatus = BtHandsfreePropertyModelInst->getCallStatus();
        NGLogDebug(LogTag_BT_Setup, "[%s] m_callStatus is: %d", __PRETTY_FUNCTION__, m_callStatus);
    }

    // connect FC request and notify
    // connect BtSettingFc
    NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingFcProxyInst is: %p", __PRETTY_FUNCTION__, BtSettingFcProxyInst);
    if (NULL != BtSettingFcProxyInst) {
        // connet this-reques() with BtSettingFcProxyInst-request()
        connect(this, SIGNAL(request(QString, QVariant)), BtSettingFcProxyInst, SIGNAL(request(QString, QVariant)));

        // connetct BtSettingFcProxyInst-notify() with this-onNotify()
        connect(BtSettingFcProxyInst, SIGNAL(notify(QString, QVariant)), this, SLOT(onNotify(QString, QVariant)));

        NGLogDebug(LogTag_BT_Setup, "[%s] connect BtSettingFcProxyInst", __PRETTY_FUNCTION__);
    }

    // connect BtHandsfreeFc
    NGLogDebug(LogTag_BT_Setup, "[%s] BtHandsfreeFcProxyInst is: %p", __PRETTY_FUNCTION__, BtHandsfreeFcProxyInst);
    if (NULL != BtHandsfreeFcProxyInst) {
        connect(BtHandsfreePropertyModelInst, SIGNAL(notifyCallStatusChanged()), this, SLOT(onHandsfreeNotify()));
        NGLogDebug(LogTag_BT_Setup, "[%s] connect BtHandsfreeFcProxyInst", __PRETTY_FUNCTION__);
    }

    // notify qml
    emit notifyRestrictionStatus();

    UIMainScreenBase::onPreActive();
}

// onActive
/*
 * unitTest's usecase
 * UT: whether the function execution is completed
*/
void STP_DevReg::onActive()
{
  /*
  * ReferenceSequence:<SequenceName # Version>
  * @datalist:<XX-XX-XX-XX # 0.000>
  */

    NGLogDebug(LogTag_BT_Setup, "View STP_DevReg did actived.");

    /*
     * To do something before UIMainScreenBase::onActive() called.
     */
    if (NULL != m_dropList) {
        m_dropList->setClip(false);
    }

    UIMainScreenBase::onActive();
}

// onPreDeactive
/*
 * unitTest's usecase
 * UT1: whether the MSG_07_09_03_00 is opened
 * UT2: whether the MSG_07_09_03_01 is opened
 * UT3: whether the MSG_07_09_03_02 is opened
 * UT4: whether the MSG_07_09_03_03 is opened
 * UT5: whether the MSG_10_01_28_02 is opened
*/
void STP_DevReg::onPreDeactive()
{
  /*
  * ReferenceSequence:<SequenceName # Version>
  * @datalist:<XX-XX-XX-XX # 0.000>
  */

    NGLogDebug(LogTag_BT_Setup, "View STP_DevReg will be deactived.");

    /*
     * To do something before UIMainScreenBase::onPreDeactive() called.
     */

    // disconnect FC request and notify
    NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingFcProxyInst is: %p", __PRETTY_FUNCTION__, BtSettingFcProxyInst);
    // if (BtSettingFcProxyInst is not NULL)
    if (NULL != BtSettingFcProxyInst) {
        // disconnet this-reques() with BtSettingFcProxyInst-request()
        disconnect(this, SIGNAL(request(QString, QVariant)), BtSettingFcProxyInst, SIGNAL(request(QString, QVariant)));

        // disconnetct BtSettingFcProxyInst-notify() with this-onNotify()
        disconnect(BtSettingFcProxyInst, SIGNAL(notify(QString, QVariant)), this, SLOT(onNotify(QString, QVariant)));

        NGLogDebug(LogTag_BT_Setup, "[%s] disconnect BtSettingFcProxyInst", __PRETTY_FUNCTION__);
    }

    // disconnect BtHandsfreeFc
    NGLogDebug(LogTag_BT_Setup, "[%s] BtHandsfreeFcProxyInst is NULL.", __PRETTY_FUNCTION__, BtHandsfreeFcProxyInst);
    if (NULL != BtHandsfreeFcProxyInst) {
        disconnect(BtHandsfreePropertyModelInst, SIGNAL(notifyCallStatusChanged()), this, SLOT(onHandsfreeNotify()));
        NGLogDebug(LogTag_BT_Setup, "[%s] connect BtHandsfreeFcProxyInst", __PRETTY_FUNCTION__);
    }

    // to do : close ons
    // close MSG_07_09_03_00
    GetNGONSAPI()->unregistCallbackByOnsId(MSG_07_09_03_00);
    GetNGONSAPI()->closeONS(MSG_07_09_03_00);
    NGLogDebug(LogTag_BT_Setup, "[%s] close MSG_07_09_03_00", __PRETTY_FUNCTION__);

    // close MSG_07_09_03_01
    GetNGONSAPI()->unregistCallbackByOnsId(MSG_07_09_03_01);
    GetNGONSAPI()->closeONS(MSG_07_09_03_01);
    NGLogDebug(LogTag_BT_Setup, "[%s] close MSG_07_09_03_01", __PRETTY_FUNCTION__);

    // close MSG_07_09_03_02
    GetNGONSAPI()->unregistCallbackByOnsId(MSG_07_09_03_02);
    GetNGONSAPI()->closeONS(MSG_07_09_03_02);
    NGLogDebug(LogTag_BT_Setup, "[%s] close MSG_07_09_03_02", __PRETTY_FUNCTION__);

    // close MSG_07_09_03_03
    GetNGONSAPI()->unregistCallbackByOnsId(MSG_07_09_03_03);
    GetNGONSAPI()->closeONS(MSG_07_09_03_03);
    NGLogDebug(LogTag_BT_Setup, "[%s] close MSG_07_09_03_03", __PRETTY_FUNCTION__);

    // close MSG_10_01_28_02 ONS
    GetNGONSAPI()->unregistCallbackByOnsId(MSG_10_01_28_02);
    GetNGONSAPI()->closeONS(MSG_10_01_28_02);
    NGLogDebug(LogTag_BT_Setup, "[%s] close MSG_10_01_28_02", __PRETTY_FUNCTION__);

    NGLogDebug(LogTag_BT_Setup, "[%s] All ONS closed", __PRETTY_FUNCTION__);

    UIMainScreenBase::onPreDeactive();
}

// onDeactive
/*
 * unitTest's usecase
 * UT: whether the function execution is completed
*/
void STP_DevReg::onDeactive()
{
  /*
  * ReferenceSequence:<SequenceName # Version>
  * @datalist:<XX-XX-XX-XX # 0.000>
  */

    NGLogDebug(LogTag_BT_Setup, "View STP_DevReg did deactived.");

    /*
     * To do something before UIMainScreenBase::onDeactive() called.
     */

    UIMainScreenBase::onDeactive();
}

// onDestroy
/*
 * unitTest's usecase
 * UT: whether the function execution is completed
*/
void STP_DevReg::onDestroy()
{
  /*
  * ReferenceSequence:<SequenceName # Version>
  * @datalist:<XX-XX-XX-XX # 0.000>
  */

    NGLogDebug(LogTag_BT_Setup, "View STP_DevReg will be destroyed.");

    /*
     * To do something before UIMainScreenBase::onDestroy() called.
     */
    // disconnect m_backBtn
    if (NULL != m_backBtn) {
        // disconnect(m_backBtn, SIGNAL(buttonClicked(int)), this, SLOT(onBackBtnClicked()))
        disconnect(m_backBtn, SIGNAL(buttonPressed(int)), this, SLOT(onBackBtnClicked()));
    }
    m_backBtn = NULL;

    // disconnect m_addr
    m_addr = 0;

    // disconnect m_name
    m_devName = "";

    // disconenct m_otherAddr
    m_otherAddr = 0;

    // disconnect m_addrStr
    m_addrStr = "";

    // disconnect m_profFlag
    m_profFlag = 0;

    // disconenct m_error
    m_error = false;

    // disconnect m_callStatus
    m_callStatus = 0;

    UIMainScreenBase::onDestroy();
}

/*---------------------------------------------------------------------------*/
// Public functions
/*---------------------------------------------------------------------------*/

// get ready for transfer to Connectting Screen
/*
 * unitTest's usecase
 * UT: whether the function execution is completed
*/
void STP_DevReg::transferToConnecting (const BtSetupCommon::DevType devType)
{
    /*
  * ReferenceSequence:<SequenceName # Version>
  * @datalist:<XX-XX-XX-XX # 0.000>
  */

    NGLogDebug(LogTag_BT_Setup, "[%s] DevType: %d", __PRETTY_FUNCTION__, devType);

    // save shareData
    NGLogDebug(LogTag_BT_Setup, "[%s] UICommonInfoPhoneInst: %p", __PRETTY_FUNCTION__, UICommonInfoPhoneInst);
    if (NULL != UICommonInfoPhoneInst) {
        // save addr in UICommon
        UICommonInfoPhoneInst->setDeviceInfo(m_addr, m_addrStr, m_devName);

        NGLogDebug(LogTag_BT_Setup, "[%s] m_addr is: %llu", __PRETTY_FUNCTION__, m_addr);
        NGLogDebug(LogTag_BT_Setup, "[%s] m_addrStr is: %s", __PRETTY_FUNCTION__, m_addrStr.toStdString().c_str());
        NGLogDebug(LogTag_BT_Setup, "[%s] m_devName is: %s", __PRETTY_FUNCTION__, m_devName.toStdString().c_str());

        // save addr in APP
        APP::SetAppContext(PhoneCommonInst->getAppId(), UI_AppContext_Key_STP_ConnStatus_DeviceMAC, QString::number(m_addr).toStdString());
        APP::SetAppContext(PhoneCommonInst->getAppId(), UI_AppContext_Key_STP_ConnStatus_DeviceName, m_devName.toStdString());
        APP::SetAppContext(PhoneCommonInst->getAppId(), UI_AppContext_Key_STP_ConnStatus_DeviceAddr, m_addrStr.toStdString());
    }

    // if LastApp is not Audio Menu
    std::string from = APP::GetShareDataStr(UI_ShareData_Key_TransFrom);
    NGLogDebug(LogTag_BT_Setup, "[%s] valueTransFrom: %s", __PRETTY_FUNCTION__, from.c_str());
    if ((UI_ShareData_Value_TransFrom_Str_BtSetting == from)\
            || (UI_ShareData_Value_TransFrom_Str_SetupAppBluetooth == from)\
            || (UI_ShareData_Value_TransFrom_Str_SetupAppPhone == from)\
            || (UI_ShareData_Value_Str_Invalid == from)\
            || (UI_ShareData_Value_TransFrom_Str_DevReplace == from)\
            || (UI_ShareData_Value_Str_PhoneAddNew == from)\
            || (UI_ShareData_Value_Str_AudioAddNew == from)) {
        // save TransFrom Val
        APP::SetShareDataStr(UI_ShareData_Key_TransFrom, UI_ShareData_Value_TransFrom_Str_DevReg);
    }

    // set connection type
    NGLogDebug(LogTag_BT_Setup, "[%s] BtSetupCommonInst: %p", __PRETTY_FUNCTION__, BtSetupCommonInst);
    if (NULL != BtSetupCommonInst) {
        BtSetupCommonInst->setDeviceType(devType);
    }

    // ScreenTransfer(STP_profConnecting)
    NGLogDebug(LogTag_BT_Setup, "[%s] MIST to [GoProfConnecting]", __PRETTY_FUNCTION__);
    APP::MIST(PhoneCommonInst->getAppId())->trigger(TRIGGER_GOPROFCONNECTING);

}

// open ONS
/*
 * unitTest's usecase
 * UT1: if ONSId is MSG_07_09_03_00
 * UT2: if ONSId is MSG_07_09_03_01
 * UT3: if ONSId is MSG_07_09_03_02
 * UT4: if ONSId is MSG_07_09_03_03
 * UT5: if ONSId is MSG_10_01_28_02
*/
void STP_DevReg::openONSWithIdAndContext(int ONSId)
{
    /*
  * ReferenceSequence:<SequenceName # Version>
  * @datalist:<XX-XX-XX-XX # X.XXX>|<YY-YY-YY-YY # Y.YYY>
  */

    NGLogDebug(LogTag_BT_Setup, "[%s] ONS %d will open", __PRETTY_FUNCTION__, ONSId);

    // if ONSId is MSG_07_09_03_00      <- UT1
    if (MSG_07_09_03_00 == ONSId) {
        // add onsContext
        NGONSContext onsContext;
        NGONSItemContext context;

        context.type = NGONSItemContextType_StringId;
        context.valueStr = std::string("MSG_MSG_07_09_03_00_RES_00");
        onsContext.textList.push_back(context);

        NGButtonRestrictionStatus backBtnRestriction = NGButtonRestrictionStatus_Disable;
        NGButtonRestrictionStatus yesBtnRestriction  = NGButtonRestrictionStatus_Disable;
        NGButtonRestrictionStatus nokBtnRestriction  = NGButtonRestrictionStatus_Disable;
        onsContext.buttonRestrictionStatusList.push_back(backBtnRestriction);
        onsContext.buttonRestrictionStatusList.push_back(yesBtnRestriction);
        onsContext.buttonRestrictionStatusList.push_back(nokBtnRestriction);

        onsContext.specId.specId1 = 6298113;
        onsContext.specId.specId2 = 6298114;
        onsContext.specId.specId3 = 6298115;

        // open ONS
        GetNGONSAPI()->openONS(ONSId, onsContext, *this);
    }
    // else if ONSId is MSG_07_09_03_01      <- UT2
    else if (MSG_07_09_03_01 == ONSId) {
        // add onsContext
        NGONSContext onsContext;
        NGONSItemContext context;

        context.type = NGONSItemContextType_StringId;
        context.valueStr = std::string("MSG_MSG_07_09_03_01_RES_00");
        onsContext.textList.push_back(context);

        // open ONS
        GetNGONSAPI()->openONS(ONSId, onsContext, *this);
    }
    // else if ONSId is MSG_07_09_03_02      <- UT3
    else if (MSG_07_09_03_02 == ONSId) {
        NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingPropertyModelInst is: %p", __PRETTY_FUNCTION__, BtSettingPropertyModelInst);
        if (NULL != BtSettingPropertyModelInst) {
            // get mainPhone name
            QString mainPhone = BtSettingPropertyModelInst->getMainPhoneName();
            NGLogDebug(LogTag_BT_Setup,  "[%s] mainPhone is: %s", __PRETTY_FUNCTION__, mainPhone.toStdString().c_str());
            QString mainName = QString().sprintf(NQResourceManagerInst.getString("MSG_MSG_07_09_03_02_RES_00").toStdString().c_str(), mainPhone.toStdString().c_str());
            NGLogDebug(LogTag_BT_Setup,  "[%s] ONS text is: %s", __PRETTY_FUNCTION__, mainName.toStdString().c_str());

            // add onsContext
            NGONSContext onsContext;
            NGONSItemContext context;

            context.type = NGONSItemContextType_RawString;
            context.valueStr = mainName.toStdString();
            onsContext.textList.push_back(context);

            NGButtonRestrictionStatus backBtnRestriction = NGButtonRestrictionStatus_Disable;
            NGButtonRestrictionStatus yesBtnRestriction  = NGButtonRestrictionStatus_Disable;
            NGButtonRestrictionStatus nokBtnRestriction  = NGButtonRestrictionStatus_Disable;
            onsContext.buttonRestrictionStatusList.push_back(backBtnRestriction);
            onsContext.buttonRestrictionStatusList.push_back(yesBtnRestriction);
            onsContext.buttonRestrictionStatusList.push_back(nokBtnRestriction);

            onsContext.specId.specId1 = 6297857;
            onsContext.specId.specId2 = 6297858;
            onsContext.specId.specId3 = 6297859;

            // open ONS
            GetNGONSAPI()->openONS(ONSId, onsContext, *this);
        }
    }
    // else if ONSId is MSG_07_09_03_03      <- UT4
    else if (MSG_07_09_03_03 == ONSId) {
        NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingPropertyModelInst is: %p", __PRETTY_FUNCTION__, BtSettingPropertyModelInst);
        if (NULL != BtSettingPropertyModelInst) {
            // get AudioPlayer name
            QString audioPlayer = BtSettingPropertyModelInst->getAudioPlayerName();
            NGLogDebug(LogTag_BT_Setup,  "[%s] audioPlayer is: %s", __PRETTY_FUNCTION__, audioPlayer.toStdString().c_str());
            QString playerName = QString().sprintf(NQResourceManagerInst.getString("MSG_MSG_07_09_03_03_RES_00").toStdString().c_str(), audioPlayer.toStdString().c_str());
            NGLogDebug(LogTag_BT_Setup,  "[%s] ONS text is: %s", __PRETTY_FUNCTION__, playerName.toStdString().c_str());

            // add onsContext
            NGONSContext onsContext;
            NGONSItemContext context;

            context.type = NGONSItemContextType_RawString;
            context.valueStr = playerName.toStdString();
            onsContext.textList.push_back(context);

            NGButtonRestrictionStatus backBtnRestriction = NGButtonRestrictionStatus_Disable;
            NGButtonRestrictionStatus yesBtnRestriction  = NGButtonRestrictionStatus_Disable;
            NGButtonRestrictionStatus nokBtnRestriction  = NGButtonRestrictionStatus_Disable;
            onsContext.buttonRestrictionStatusList.push_back(backBtnRestriction);
            onsContext.buttonRestrictionStatusList.push_back(yesBtnRestriction);
            onsContext.buttonRestrictionStatusList.push_back(nokBtnRestriction);

            onsContext.specId.specId1 = 6297885;
            onsContext.specId.specId2 = 6297886;
            onsContext.specId.specId3 = 6297887;

            // open ONS
            GetNGONSAPI()->openONS(ONSId, onsContext, *this);
        }
    }
    // else if ONSId is MSG_10_01_28_02      <- UT5
    else if (MSG_10_01_28_02 == ONSId) {
        // add onsContext
        NGONSContext onsContext;
        NGONSItemContext context;

        context.type = NGONSItemContextType_StringId;
        context.valueStr = std::string("MSG_MSG_10_01_28_02_RES_00");
        onsContext.textList.push_back(context);

        NGButtonRestrictionStatus backBtnRestriction = NGButtonRestrictionStatus_Disable;
        NGButtonRestrictionStatus yesBtnRestriction  = NGButtonRestrictionStatus_Disable;
        onsContext.buttonRestrictionStatusList.push_back(backBtnRestriction);
        onsContext.buttonRestrictionStatusList.push_back(yesBtnRestriction);

        onsContext.specId.specId1 = 6298369;
        onsContext.specId.specId2 = 6298370;

        // open ONS
        GetNGONSAPI()->openONS(ONSId, onsContext, *this);
    }
    else {
        NGLogDebug(LogTag_BT_Setup, "[%s] ONSId error", __PRETTY_FUNCTION__);
    }

    // init OnsStstus
    initOnsStatus();
}

/*---------------------------------------------------------------------------*/
// Public slots functions
/*---------------------------------------------------------------------------*/

// click DevName button
/*
 * unitTest's usecase
 * UT: whether the function execution is completed
*/
void STP_DevReg::onDevNameBtnClicked(QString m_name, quint64 m_bdAddr, QString m_bdAddrStr)
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<XX-XX-XX-XX # 0.000>
    */

    m_devName = m_name;
    m_addr = m_bdAddr;
    m_addrStr = m_bdAddrStr;

    // save shareData
    NGLogDebug(LogTag_BT_Setup, "[%s] UICommonInfoPhoneInst: %p", __PRETTY_FUNCTION__, UICommonInfoPhoneInst);
    if (NULL != UICommonInfoPhoneInst) {
        UICommonInfoPhoneInst->setDeviceInfo(m_addr, m_addrStr, m_devName);
    }

    // set FC DevName and BtAddr
    if (NULL != BtSettingFcProxyInst) {
        QMap<QString, QVariant> qmap;
        qmap.insert(FC_BT_SETTING_PAR_KEY_ADDRESS, m_addr);
        emit request(FC_BT_SETTING_REQ_GET_PAIRED_DEVICE_INFO_FROM_LIST_MODEL, QVariant(qmap));
        NGLogDebug(LogTag_BT_Setup, "[%s] request FC Device info", __PRETTY_FUNCTION__);
    }
}

// click HFP button
/*
 * unitTest's usecase
 * UT1: if region is Oceania and HFP is not available
 * UT2: if region is Oceania and main HFP has connected
 * UT3: if region is Oceania and main HFP has not connected
 * UT4: if region is China or EU and data is communicating
 * UT5: if region is China or EU and main HFP has connected
 * UT6: if region is China or EU and main HFP has not connected
 * UT7: if region is Other and main HFP has connected
 * UT8: if region is Other and main HFP has not connected
 *
*/
void STP_DevReg::onHfpBtnClicked(QString m_name, quint64 m_bdAddr, QString m_bdAddrStr)
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<XX-XX-XX-XX # 0.000>
    */

    NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingPropertyModelInst is: %p", __PRETTY_FUNCTION__, BtSettingPropertyModelInst);
    if (NULL == BtSettingPropertyModelInst) {
        return;
    }
    NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingPairedDeviceInfoModelInst is: %p", __PRETTY_FUNCTION__, BtSettingPairedDeviceInfoModelInst);
    if (NULL == BtSettingPairedDeviceInfoModelInst) {
        return;
    }

    m_profFlag = BtSetupCommon::DevType_MainPhone;

    m_devName = m_name;
    m_addr = m_bdAddr;
    m_addrStr = m_bdAddrStr;

    bool isOceania = PhoneCommon::GetInstance()->getUICFunc()->kindPNR().isRegion_OCEANIA();
    bool isEU = PhoneCommon::GetInstance()->getUICFunc()->kindPNR().isRegion_EU();
    bool isChina = PhoneCommon::GetInstance()->getUICFunc()->kindPNR().isRegion_CHINA();

    NGLogDebug(LogTag_BT_Setup,  "[%s] isOceania is: %d", __PRETTY_FUNCTION__, isOceania);
    NGLogDebug(LogTag_BT_Setup,  "[%s] isEU is: %d", __PRETTY_FUNCTION__, isEU);
    NGLogDebug(LogTag_BT_Setup,  "[%s] isChina is: %d", __PRETTY_FUNCTION__, isChina);

    // if is Oceania
    if (isOceania) {
        // if HFP is not available      <- UT1
        NGLogDebug(LogTag_BT_Setup,  "[%s] isHFPAvailable is: %d", __PRETTY_FUNCTION__, BtSettingPropertyModelInst->isHFPAvailable());
        if (!(BtSettingPropertyModelInst->isHFPAvailable())) {
            // open ONS HFP is not Available
            NGLogDebug(LogTag_BT_Setup, "[%s] readly to open MSG_10_01_28_02", __PRETTY_FUNCTION__);
            this->openONSWithIdAndContext(MSG_10_01_28_02);
        }
        // else if HFP is available
        else {
            // if main HFP has connected        <- UT2
            NGLogDebug(LogTag_BT_Setup,  "[%s] SystemInfoHFPMain is: %d", __PRETTY_FUNCTION__, BtSettingPropertyModelInst->getHfpConnectedStatus());
            if (BtSettingPropertyModelInst->getHfpConnectedStatus()) {
                // open ONS to stop other main HFP
                NGLogDebug(LogTag_BT_Setup, "[%s] readly to open MSG_07_09_03_02", __PRETTY_FUNCTION__);
                this->openONSWithIdAndContext(MSG_07_09_03_02);
            }
            // else if main HFP has not connected       <- UT3
            else {
                NGLogDebug(LogTag_BT_Setup, "[%s] readly to ScreenTransfer", __PRETTY_FUNCTION__);
                // ScreenTransfer STP_profConnecting (connect as main phone)
                this->transferToConnecting(BtSetupCommon::DevType_MainPhone);
            }
        }
    }
    // else if EU and China
    else if (isEU || isChina) {
        // if data is communicating     <- UT4
        NGLogDebug(LogTag_BT_Setup,  "[%s] isDataCommunicating is: %d", __PRETTY_FUNCTION__, BtSettingPropertyModelInst->isDataCommunication());
        if (BtSettingPropertyModelInst->isDataCommunication()) {
            NGLogDebug(LogTag_BT_Setup,  "[%s] the data is communicating", __PRETTY_FUNCTION__);
            // open ONS to stop data communicating
            this->openONSWithIdAndContext(MSG_07_09_03_00);
        }
        // else if data is not communicating
        else {
            // if main HFP has connected        <- UT5
            NGLogDebug(LogTag_BT_Setup,  "[%s] SystemInfoHFPMain is: %d", __PRETTY_FUNCTION__, BtSettingPropertyModelInst->getHfpConnectedStatus());
            if (BtSettingPropertyModelInst->getHfpConnectedStatus()) {
                // open ONS to stop other main HFP
                NGLogDebug(LogTag_BT_Setup, "[%s] readly to open MSG_07_09_03_02", __PRETTY_FUNCTION__);
                this->openONSWithIdAndContext(MSG_07_09_03_02);
            }
            // else if main HFP has not connected       <- UT6
            else {
                NGLogDebug(LogTag_BT_Setup, "[%s] readly to ScreenTransfer", __PRETTY_FUNCTION__);
                // ScreenTransfer STP_profConnecting (connect as main phone)
                this->transferToConnecting(BtSetupCommon::DevType_MainPhone);
            }
        }
    }
    // else if other region
    else {
        // if main HFP has connected        <- UT7
        NGLogDebug(LogTag_BT_Setup,  "[%s] SystemInfoHFPMain is: %d", __PRETTY_FUNCTION__, BtSettingPropertyModelInst->getHfpConnectedStatus());
        if (BtSettingPropertyModelInst->getHfpConnectedStatus()) {
            // open ONS to stop other main HFP
            NGLogDebug(LogTag_BT_Setup, "[%s] readly to open MSG_07_09_03_02", __PRETTY_FUNCTION__);
            this->openONSWithIdAndContext(MSG_07_09_03_02);
        }
        // else if main HFP has not connected       <- UT8
        else {
            NGLogDebug(LogTag_BT_Setup, "[%s] readly to ScreenTransfer", __PRETTY_FUNCTION__);
            // ScreenTransfer STP_profConnecting (connect as main phone)
            this->transferToConnecting(BtSetupCommon::DevType_MainPhone);
        }
    }
}

// click AVP button
/*
 * unitTest's usecase
 * UT1: if region is China or EU and data is communicating
 * UT2: if region is China or EU and other device has connected AVP
 * UT3: if region is China or EU and other device has not connected AVP
 * UT4: if region is Other and other device has connected AVP
 * UT5: if region is Other and other device has not connected AVP
*/
void STP_DevReg::onAvpBtnClicked(QString m_name, quint64 m_bdAddr, QString m_bdAddrStr)
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<XX-XX-XX-XX # 0.000>
    */

    NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingPropertyModelInst is: %p", __PRETTY_FUNCTION__, BtSettingPropertyModelInst);
    if (NULL == BtSettingPropertyModelInst) {
        return;
    }
    NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingPairedDeviceInfoModelInst is: %p", __PRETTY_FUNCTION__, BtSettingPairedDeviceInfoModelInst);
    if (NULL == BtSettingPairedDeviceInfoModelInst) {
        return;
    }

    m_profFlag = BtSetupCommon::DevType_Audio;

    m_devName = m_name;
    m_addr = m_bdAddr;
    m_addrStr = m_bdAddrStr;

    bool isEU = PhoneCommon::GetInstance()->getUICFunc()->kindPNR().isRegion_EU();
    bool isChina = PhoneCommon::GetInstance()->getUICFunc()->kindPNR().isRegion_CHINA();

    NGLogDebug(LogTag_BT_Setup,  "[%s] isEU is: %d", __PRETTY_FUNCTION__, isEU);
    NGLogDebug(LogTag_BT_Setup,  "[%s] isChina is: %d", __PRETTY_FUNCTION__, isChina);

    // if is EU and China
    if (isEU || isChina) {
        // if data is communicating     <- UT1
        NGLogDebug(LogTag_BT_Setup,  "[%s] isDataCommunicating is: %d", __PRETTY_FUNCTION__, BtSettingPropertyModelInst->isDataCommunication());
        if (BtSettingPropertyModelInst->isDataCommunication()) {
            // open ONS to stop data communicating
            this->openONSWithIdAndContext(MSG_07_09_03_00);
        }
        // else if data is not communicating
        else {
            // if other device has connected AVP        <- UT2
            NGLogDebug(LogTag_BT_Setup,  "[%s] getAvpConnectedStatus is: %d", __PRETTY_FUNCTION__, BtSettingPropertyModelInst->getAvpConnectedStatus());
            if (BtSettingPropertyModelInst->getAvpConnectedStatus()) {
                // open MSG_07_09_03_03
                this->openONSWithIdAndContext(MSG_07_09_03_03);
            }
            // else if other device has not connected AVP       <- UT3
            else {
                // ScreenTransfer STP_profConnecting (connect as audio player)
                this->transferToConnecting(BtSetupCommon::DevType_Audio);
            }
        }
    }
    // else if is other region
    else {
        // if other device has connected AVP        <- UT4
        NGLogDebug(LogTag_BT_Setup,  "[%s] getAvpConnectedStatus is: %d", __PRETTY_FUNCTION__, BtSettingPropertyModelInst->getAvpConnectedStatus());
        if (BtSettingPropertyModelInst->getAvpConnectedStatus()) {
            // open MSG_07_09_03_03
            this->openONSWithIdAndContext(MSG_07_09_03_03);
        }
        // else if other device has not connected AVP       <- UT5
        else {
            // ScreenTransfer STP_profConnecting (connect as audio player)
            this->transferToConnecting(BtSetupCommon::DevType_Audio);
        }
    }
}

// click Back button
/*
 * unitTest's usecase
 * UT1: if transfrom is SourceSelect
 * UT2: else if transfrom is DevReplace
 * UT3: else
*/
void STP_DevReg::onBackBtnClicked()
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<XX-XX-XX-XX # 0.000>
    */

    // get sharedata of transfrom
    std::string from = APP::GetShareDataStr(UI_ShareData_Key_TransFrom);
    // set sharedata of transfrom is invalid
    APP::SetShareDataStr(UI_ShareData_Key_TransFrom, UI_ShareData_Value_Str_Invalid);

    // if transfrom is SourceSelect     <- UT1
    if ((UI_ShareData_Value_TransFrom_Str_SourceSelect == from)\
            || (UI_ShareData_Value_Str_AudioAddNew == from)) {
        // transferScreen to LastApp
        NGLogDebug(LogTag_BT_Setup, "[%s] MIST to [GOLASTAPP]", __PRETTY_FUNCTION__);
        APP::MIST(PhoneCommonInst->getAppId())->trigger(TRIGGER_GOLASTAPP);
    }
//    // else if transfrom is DevReplace      <- UT2
//    else if (UI_ShareData_Value_TransFrom_Str_DevReplace == from) {
//        // transferScreen to BTSetting
//        NGLogDebug(LogTag_BT_Setup,  "[%s] MIST to [GOBTSETTING]", __PRETTY_FUNCTION__);
//        APP::MIST(PhoneCommonInst->getAppId())->trigger(TRIGGER_GOBTSETTING);
//    }
    // else     <- UT3
    else {
        // transferScreen to TopBack
        NGLogDebug(LogTag_BT_Setup, "[%s] MIST to [GoTopBack]", __PRETTY_FUNCTION__);
        APP::MIST(PhoneCommonInst->getAppId())->trigger(TRIGGER_GOTOPBACK);
    }
}

// close ONS
/*
 * unitTest's usecase
 * UT: whether the function execution is completed
*/
void STP_DevReg::onONSClosed(int ONSId)
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<XX-XX-XX-XX # 0.000>
    */

    NGLogDebug(LogTag_BT_Setup, "[%s] called", __PRETTY_FUNCTION__);

    NGLogDebug(LogTag_BT_Setup,  "[%s] ONSId is: %d", __PRETTY_FUNCTION__, ONSId);
    // ONS to show data is stopping communication
    if (MSG_07_09_03_01 == ONSId) {
        NGLogDebug(LogTag_BT_Setup,  "[%s] MSG_07_09_03_01 is closed and second connectting", __PRETTY_FUNCTION__);
        // second connect bluetooth
        this->secondConnect();
    }
}

// click ONS
/*
 * unitTest's usecase
 * UT1: ONSID is MSG_07_09_03_00 and btnId is yes
 * UT2: ONSID is MSG_07_09_03_00 and btnId is No or back
 * UT3: ONSID is MSG_07_09_03_00 and btnId is error
 * UT4: ONSID is MSG_07_09_03_02 and btnId is yes
 * UT5: ONSID is MSG_07_09_03_02 and btnId is No or back
 * UT6: ONSID is MSG_07_09_03_02 and btnId is error
 * UT7: ONSID is MSG_07_09_03_03 and btnId is yes
 * UT8: ONSID is MSG_07_09_03_03 and btnId is No or back
 * UT9: ONSID is MSG_07_09_03_03 and btnId is error
 * UT10: ONSID is error
*/
void STP_DevReg::onONSClicked(int ONSId, int btnId)
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<XX-XX-XX-XX # X.XXX>|<YY-YY-YY-YY # Y.YYY>
    */

    NGLogDebug(LogTag_BT_Setup, "onONSClicked:: [ %d ]", ONSId);
    NGLogDebug(LogTag_BT_Setup, "onONSClicked:: [ %d ]", btnId);
    // ONS to stop data communicating or not
    if (MSG_07_09_03_00 == ONSId) {
        // if btnId is Yes      <- UT1
        if (NGONSBtnId_First == btnId) {
            if (NULL != BtSettingFcProxyInst) {
                // to stop data communicating
                if (NULL != BtSettingFcProxyInst) {
                    QMap<QString, QVariant> qmap;
                    qint64 m_mainPhone = BtSettingMainDeviceInfoModelInst->getBdAddr();
                    qmap.insert(FC_BT_SETTING_PAR_KEY_ADDRESS, m_mainPhone);
                    emit request(FC_BT_SETTING_REQ_DISCONNECT_DATA_COMUUNICATION, QVariant(qmap));

                    // open MSG_07_09_03_01
                    this->openONSWithIdAndContext(MSG_07_09_03_01);
                }
            }
        }
        // else if btnId is No or back      <- UT2
        else if ((NGONSBtnId_Second == btnId) || (NGONSBtnId_Back == btnId)) {
            NGLogDebug(LogTag_BT_Setup, "[%s] btnId: [%d]", __PRETTY_FUNCTION__, btnId);
        }
        // else if btnId is error       <- UT3
        else {
            NGLogDebug(LogTag_BT_Setup, "[%s] btnId error", __PRETTY_FUNCTION__);
        }
        // GetNGONSAPI()->unregisterONSCallBack(*this);
    }
    // ONS to disconnect other HFP or not
    else if (MSG_07_09_03_02 == ONSId) {
        // if btnId is Yes      <- UT4
        if (NGONSBtnId_First == btnId) {
            if (NULL != BtSettingFcProxyInst) {
                // to disconnect other HFP
                QMap<QString, QVariant> qmap;
                qint16 m_profile = BtSetting_DeviceType_MainPhone;
                qmap.insert(FC_BT_SETTING_PAR_KEY_ADDRESS, m_otherAddr);
                qmap.insert(FC_BT_SETTING_PAR_KEY_DEVICE_TYPE, m_profile);
                emit request(FC_BT_SETTING_REQ_DISCONNECT_DEVICE_TYPE, QVariant(qmap));
                NGLogDebug(LogTag_BT_Setup, "[%s] Request FC disconnect all other HFP", __PRETTY_FUNCTION__);
                // To be delete: ScreenTransfer STP_profConnecting (connect as main phone)
                // this->transferToConnecting(BtSetupCommon::DevType_MainPhone);
            }
        }
        // else if btnId is No or back      <- UT5
        else if ((NGONSBtnId_Second == btnId) || (NGONSBtnId_Back == btnId)) {
            NGLogDebug(LogTag_BT_Setup, "[%s] btnId: [%d]", __PRETTY_FUNCTION__, btnId);
        }
        // else if btnId is error       <- UT6
        else {
            NGLogDebug(LogTag_BT_Setup, "[%s] btnId error", __PRETTY_FUNCTION__);
        }
        // GetNGONSAPI()->unregisterONSCallBack(*this);
    }
    // ONS to disconnect other AVP or not
    else if (MSG_07_09_03_03 == ONSId) {
        // if btnId is Yes      <- UT7
        if (NGONSBtnId_First == btnId) {
            if (NULL != BtSettingFcProxyInst) {
                // to disconnect other AVP
                if (NULL != BtSettingFcProxyInst) {
                    // to disconnect other AVP
                    QMap<QString, QVariant> qmap;
                    qint16 m_profile = BtSetting_DeviceType_AudioPlayer;
                    qmap.insert(FC_BT_SETTING_PAR_KEY_ADDRESS, m_otherAddr);
                    qmap.insert(FC_BT_SETTING_PAR_KEY_DEVICE_TYPE, m_profile);
                    emit request(FC_BT_SETTING_REQ_DISCONNECT_DEVICE_TYPE, QVariant(qmap));
                    NGLogDebug(LogTag_BT_Setup, "[%s] Request FC disconnect all other AVP", __PRETTY_FUNCTION__);
                }
                // To be delete: ScreenTransfer STP_profConnecting (connect as audio player)
                // this->transferToConnecting(BtSetupCommon::DevType_Audio);
            }
        }
        // else if btnId is No or back      <- UT8
        else if ((NGONSBtnId_Second == btnId) || (NGONSBtnId_Back == btnId)) {
            NGLogDebug(LogTag_BT_Setup, "[%s] btnId: [%d]", __PRETTY_FUNCTION__, btnId);
        }
        // else if btnId is error       <- UT9
        else {
            NGLogDebug(LogTag_BT_Setup, "[%s] btnId error", __PRETTY_FUNCTION__);
        }
        // GetNGONSAPI()->unregisterONSCallBack(*this);
    }
    // else if ONSId is error       <- UT10
    else {
        NGLogDebug(LogTag_BT_Setup, "[%s] ONSId error", __PRETTY_FUNCTION__);
    }
}

// notify from FC
/*
 * unitTest's usecase
 * UT1: uri is set DevName and BdAddr in FC finish
 * UT2: uri is disconnect device complete and type is mainPhone
 * UT3: uri is disconnect device complete and type is AudioPlayer
 * UT4: uri is disconnect device complete and type is error
 * UT5: uri is BT error mode automatic return processing
 * UT6: uri is disconnect data communicating finish
 * UT7: uri is error
*/
void STP_DevReg::onNotify(QString uri, QVariant data)
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<XX-XX-XX-XX # X.XXX>|<YY-YY-YY-YY # Y.YYY>
    */

    // if set DevName and BdAddr in FC finish     <- UT1
    if (FC_BT_SETTING_NOTIFY_GET_DEVICE_INFO_FROM_LIST_MODEL_FINISH == uri) {
        NGLogDebug(LogTag_BT_Setup, "[%s] notify fc Device Info", __PRETTY_FUNCTION__);

        NGLogDebug(LogTag_BT_Setup, "[%s] m_addr is: %llu", __PRETTY_FUNCTION__, m_addr);
        NGLogDebug(LogTag_BT_Setup, "[%s] m_addrStr is: %s", __PRETTY_FUNCTION__, m_addrStr.toStdString().c_str());
        NGLogDebug(LogTag_BT_Setup, "[%s] m_devName is: %s", __PRETTY_FUNCTION__, m_devName.toStdString().c_str());

        // save addr in APP
        APP::SetAppContext(PhoneCommonInst->getAppId(), UI_AppContext_Key_STP_ConnStatus_DeviceMAC, QString::number(m_addr).toStdString());
        APP::SetAppContext(PhoneCommonInst->getAppId(), UI_AppContext_Key_STP_ConnStatus_DeviceName, m_devName.toStdString());
        APP::SetAppContext(PhoneCommonInst->getAppId(), UI_AppContext_Key_STP_ConnStatus_DeviceAddr, m_addrStr.toStdString());

        NGLogDebug(LogTag_BT_Setup, "[%s] MIST to [GoConnStatus]", __PRETTY_FUNCTION__);
        APP::MIST(PhoneCommonInst->getAppId())->trigger(TRIGGER_GOCONNSTATUS);
    }
    // else if disconnect device complete
    else if (FC_BT_SETTING_NOTIFY_DISCONNECT_DEVICE_TYPE_FINISH == uri) {
        QMap<QString, QVariant> qMap = data.toMap();
        // get BtAddr from (data -> QMap)
        if (!qMap.contains(FC_BT_SETTING_PAR_KEY_ADDRESS)) {
            return;
        }
        QMap<QString, QVariant>::iterator numAddr = qMap.find(FC_BT_SETTING_PAR_KEY_ADDRESS);
        quint64 addr = numAddr.value().toUInt();
        // if BtAddr belong to the device
        if (m_otherAddr == addr) {
            // get device profile
            if (!qMap.contains(FC_BT_SETTING_PAR_KEY_DEVICE_TYPE)) {
                return;
            }
            QMap<QString, QVariant>::iterator numProf = qMap.find(FC_BT_SETTING_PAR_KEY_DEVICE_TYPE);
            quint64 profile = numProf.value().toInt();
            // if diasconnect mainPhone         <- UT2
            if (BtSetting_DeviceType_MainPhone == profile) {
                NGLogDebug(LogTag_BT_Setup,  "[%s] receive notify disconnect other main Phone finish", __PRETTY_FUNCTION__);
                NGLogDebug(LogTag_BT_Setup,  "[%s] getHfpConnectedStatus is: %d", __PRETTY_FUNCTION__, BtSettingPropertyModelInst->getHfpConnectedStatus());
                if (BtSettingPropertyModelInst->getHfpConnectedStatus()) {

                    return;
                }

                // onHfpBtnClicked second time
                this->onHfpBtnClicked(m_devName, m_addr, m_addrStr);
            }
            // if disconnect AVP        <- UT3
            else if (BtSetting_DeviceType_AudioPlayer == profile) {
                NGLogDebug(LogTag_BT_Setup,  "[%s] receive notify disconnect other Audio finish", __PRETTY_FUNCTION__);
                NGLogDebug(LogTag_BT_Setup,  "[%s] getAvpConnectedStatus is: %d", __PRETTY_FUNCTION__, BtSettingPropertyModelInst->getAvpConnectedStatus());
                if (BtSettingPropertyModelInst->getAvpConnectedStatus()) {

                    return;
                }

                // onAvpBtnClicked sceond time
                this->onAvpBtnClicked(m_devName, m_addr, m_addrStr);
            }
            // else if profile is error     <-UT4
            else {
                NGLogDebug(LogTag_BT_Setup,  "[%s] receive notify of disconnect other device error", __PRETTY_FUNCTION__);
            }
        }
    }
    // else if BT error mode automatic return processing        <-UT5
    else if (FC_BT_SETTING_NOTIFY_ERROR_MODE_CHANGED == uri) {
        QMap<QString, QVariant> qMap = data.toMap();
        // get BtAddr from (data -> QMap)
        if (!qMap.contains(FC_BT_SETTING_PAR_ERROR_RESET_STATUS)) {
            return;
        }
        QMap<QString, QVariant>::iterator erroStatus = qMap.find(FC_BT_SETTING_PAR_ERROR_RESET_STATUS);
        m_error = erroStatus.value().toBool();

        NGLogDebug(LogTag_BT_Setup,  "[%s] receive notify of error mode: %d", __PRETTY_FUNCTION__, m_error);
        // init OnsStstus
        initOnsStatus();
    }
    // else if disconnect data communicating finish         <-UT6
    else if (FC_BT_SETTING_NOTIFY_DISCONNECT_DATA_COMMUNICATION_FINISH == uri) {
        NGLogDebug(LogTag_BT_Setup,  "[%s] receive notify of disconnect data communicating finish", __PRETTY_FUNCTION__);
//        // close MSG_07_09_03_01
//        if (NGONSStatus_Closed != GetNGONSAPI()->getONSStatus(MSG_07_09_03_01)) {
//            NGLogDebug(LogTag_BT_Setup,  "[%s] MSG_07_09_03_01 is not closed", __PRETTY_FUNCTION__);
//            GetNGONSAPI()->closeONS(MSG_07_09_03_01);
//            NGLogDebug(LogTag_BT_Setup, "[%s] close MSG_07_09_03_01", __PRETTY_FUNCTION__);
//        }

        // if MSG_07_09_03_01 is closed
        if (NGONSStatus_Closed == GetNGONSAPI()->getONSStatus(MSG_07_09_03_01)) {
            NGLogDebug(LogTag_BT_Setup,  "[%s] MSG_07_09_03_01 is closed and disconnect data communicating finish", __PRETTY_FUNCTION__);
            // second connect bluetooth
            this->secondConnect();
        }
    }
    // else if uri is eror         <-UT7
    else {
        NGLogDebug(LogTag_BT_Setup,  "[%s] receive notify error", __PRETTY_FUNCTION__);
    }
}

// get handsfree call status
/*
 * unitTest's usecase
 * UT: whether the function execution is completed
*/
void STP_DevReg::onHandsfreeNotify()
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<XX-XX-XX-XX # X.XXX>|<YY-YY-YY-YY # Y.YYY>
    */

    NGLogDebug(LogTag_BT_Setup, "[%s] called", __PRETTY_FUNCTION__);

    NGLogDebug(LogTag_BT_Setup, "[%s] BtHandsfreePropertyModelInst is: %p", __PRETTY_FUNCTION__, BtHandsfreePropertyModelInst);
    if (NULL == BtHandsfreePropertyModelInst) {
        return;
    }
    // get call status      <-UT1
    m_callStatus = BtHandsfreePropertyModelInst->getCallStatus();
    NGLogDebug(LogTag_BT_Setup, "[%s] callStatus is: %d", __PRETTY_FUNCTION__, m_callStatus);

    // init OnsStstus
    initOnsStatus();
}

/*
 * unitTest's usecase
 * UT1: if in Bt error mode
 * UT2: if callstatus is idle
 * UT3: if callstatus is not idle
 * UT4: if device is disconencted
*/
// set ONS button status with error mode
void STP_DevReg::setOnsButtonStatusWithErrorMode(int onsId)
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<XX-XX-XX-XX # 0.000>
    */

    NGONSContext onsContext;
    onsContext.option = NGContextOption_ButtonState;
    // set back button
    onsContext.buttonStateList.push_back(NGButtonState_Active);

    // if onsId is opened
    if (NGONSStatus_Closed != GetNGONSAPI()->getONSStatus(onsId)) {
        // set Yes button
        // if in Bt error mode      // UT1
        if (m_error) {
            onsContext.buttonStateList.push_back(NGButtonState_Inactive);
        }
        // else if HFP main or sub has connected
        else if ((BtSettingPropertyModelInst->getHfpConnectedStatus()) || (BtSettingPropertyModelInst->getSubHfpConnectedStatus())) {
            // if is not talking,sending,receiving      // UT2
            if (BtHandsfreeEnum::CallStatus_Idle == m_callStatus) {
                onsContext.buttonStateList.push_back(NGButtonState_Active);
            }
            // else if is talking,sending,receiving     // UT3
            else {
                onsContext.buttonStateList.push_back(NGButtonState_Inactive);
            }
        }
        // else if HFP main or sub has not connected        // UT4
        else {
            onsContext.buttonStateList.push_back(NGButtonState_Active);
        }

        // set No btton
        // if HFP main or sub has connected
        if ((BtSettingPropertyModelInst->getHfpConnectedStatus()) || (BtSettingPropertyModelInst->getSubHfpConnectedStatus())) {
            // if is not talking,sending,receiving
            if (BtHandsfreeEnum::CallStatus_Idle == m_callStatus) {
                onsContext.buttonStateList.push_back(NGButtonState_Active);
            }
            // else if is talking,sending,receiving
            else {
                onsContext.buttonStateList.push_back(NGButtonState_Inactive);
            }
        }
        // else if HFP main or sub has not connected
        else {
            onsContext.buttonStateList.push_back(NGButtonState_Active);
        }

        // set button status to ONS
        NGLogDebug(LogTag_BT_Setup, "[%s] GetNGONSAPI() is: %p", __PRETTY_FUNCTION__, GetNGONSAPI());
        if (NULL != GetNGONSAPI()) {
            NGLogDebug(LogTag_BT_Setup, "[%s] ONS: %d is %d", __PRETTY_FUNCTION__, onsId, GetNGONSAPI()->getONSStatus(onsId));
            if (NGONSStatus_Closed != GetNGONSAPI()->getONSStatus(onsId)) {
               GetNGONSAPI()->updateONS(onsId, onsContext);
            }
            NGLogDebug(LogTag_BT_Setup, "[%s] ONS: %d is %d", __PRETTY_FUNCTION__, onsId, GetNGONSAPI()->getONSStatus(onsId));
        }

    }
}


/*
 * unitTest's usecase
 * UT1: if callstatus is idle
 * UT2: if callstatus is not idle
 * UT3: if device is disconencted
*/
// set ONS button status without error mode
void STP_DevReg::setOnsButtonStatusWithoutErrorMode(int onsId)
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<XX-XX-XX-XX # 0.000>
    */

    NGONSContext onsContext;
    onsContext.option = NGContextOption_ButtonState;
    // set back button
    onsContext.buttonStateList.push_back(NGButtonState_Active);

    // if onsId is opened
    if (NGONSStatus_Closed != GetNGONSAPI()->getONSStatus(onsId)) {
        // set Yes and No button
        // else if HFP main or sub has connected
        if ((BtSettingPropertyModelInst->getHfpConnectedStatus()) || (BtSettingPropertyModelInst->getSubHfpConnectedStatus())) {
            // if is not talking,sending,receiving      //UT1
            if (BtHandsfreeEnum::CallStatus_Idle == m_callStatus) {
                onsContext.buttonStateList.push_back(NGButtonState_Active);
                onsContext.buttonStateList.push_back(NGButtonState_Active);
            }
            // else if is talking,sending,receiving     // UT2
            else {
                onsContext.buttonStateList.push_back(NGButtonState_Inactive);
                onsContext.buttonStateList.push_back(NGButtonState_Inactive);
            }
        }
        // else if HFP main or sub has not connected    // UT3
        else {
            onsContext.buttonStateList.push_back(NGButtonState_Active);
            onsContext.buttonStateList.push_back(NGButtonState_Active);
        }

        // set button status to ONS
        NGLogDebug(LogTag_BT_Setup, "[%s] GetNGONSAPI() is: %p", __PRETTY_FUNCTION__, GetNGONSAPI());
        if (NULL != GetNGONSAPI()) {
            NGLogDebug(LogTag_BT_Setup, "[%s] ONS: %d is %d", __PRETTY_FUNCTION__, onsId, GetNGONSAPI()->getONSStatus(onsId));
            if (NGONSStatus_Closed != GetNGONSAPI()->getONSStatus(onsId)) {
               GetNGONSAPI()->updateONS(onsId, onsContext);
            }
            NGLogDebug(LogTag_BT_Setup, "[%s] ONS: %d is %d", __PRETTY_FUNCTION__, onsId, GetNGONSAPI()->getONSStatus(onsId));
        }
    }
}


/*
 * unitTest's usecase
 * UT: whether the function execution is completed
*/
// init OnsStstus
void STP_DevReg::initOnsStatus()
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<XX-XX-XX-XX # 0.000>
    */

    NGLogDebug(LogTag_BT_Setup, "[%s] called", __PRETTY_FUNCTION__);
    this->setOnsButtonStatusWithErrorMode(MSG_07_09_03_02);
    this->setOnsButtonStatusWithErrorMode(MSG_07_09_03_03);
    this->setOnsButtonStatusWithoutErrorMode(MSG_07_09_03_00);
}

// second connectting after disconnect data communicating finish
/*
 * unitTest's usecase
 * UT1: profFlag is mainPhone and other device has connected
 * UT2: profFlag is mainPhone and other device has not connected
 * UT3: profFlag is audioPlayer and other device has connected
 * UT4: profFlag is audioPlayer and other device has not connected
 * UT5: profFlag is error
*/
void STP_DevReg::secondConnect()
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<XX-XX-XX-XX # 0.000>
    */

    NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingPropertyModelInst is: %p", __PRETTY_FUNCTION__, BtSettingPropertyModelInst);
    if (NULL == BtSettingPropertyModelInst) {
        return;
    }

    NGLogDebug(LogTag_BT_Setup,  "[%s] isDataCommunicating is: %d", __PRETTY_FUNCTION__, BtSettingPropertyModelInst->isDataCommunication());
    if (BtSettingPropertyModelInst->isDataCommunication()) {
        NGLogDebug(LogTag_BT_Setup, "[%s] stop communicating failed", __PRETTY_FUNCTION__);
        return;
    }

    // if connect main HFP
    if (BtSetupCommon::DevType_MainPhone == m_profFlag) {
        // if main Phone has connected      <- UT1
        NGLogDebug(LogTag_BT_Setup,  "[%s] getHfpConnectedStatus is: %d", __PRETTY_FUNCTION__, BtSettingPropertyModelInst->getHfpConnectedStatus());
        if (BtSettingPropertyModelInst->getHfpConnectedStatus()) {
            // open MSG_07_09_03_02
            this->openONSWithIdAndContext(MSG_07_09_03_02);
        }
        // else if main Phone has not connected     <- UT2
        else {
            NGLogDebug(LogTag_BT_Setup, "[%s] readly to ScreenTransfer connect mainPhone", __PRETTY_FUNCTION__);
            // ScreenTransfer STP_profConnecting (connect as main phone)
            this->transferToConnecting(BtSetupCommon::DevType_MainPhone);
        }
    }
    // else if connect Audio Player
    else if (BtSetupCommon::DevType_Audio == m_profFlag) {
        // if AVP has connected     <- UT3
        NGLogDebug(LogTag_BT_Setup,  "[%s] getAvpConnectedStatus is: %d", __PRETTY_FUNCTION__, BtSettingPropertyModelInst->getAvpConnectedStatus());
        if (BtSettingPropertyModelInst->getAvpConnectedStatus()) {
            // open MSG_07_09_03_03
            this->openONSWithIdAndContext(MSG_07_09_03_03);
        }
        // else if AVP has not connected        <- UT4
        else {
            NGLogDebug(LogTag_BT_Setup, "[%s] readly to ScreenTransfer connect Audio", __PRETTY_FUNCTION__);
            // ScreenTransfer STP_profConnecting (connect as audio player)
            this->transferToConnecting(BtSetupCommon::DevType_Audio);
        }
    }
    // else if connect unknow type      <- UT5
    else {
        NGLogDebug(LogTag_BT_Setup, "[%s] m_profFlag is error", __PRETTY_FUNCTION__);
    }
}

/*
 * unitTest's usecase
 * UT: whether the function execution is completed
*/
// vehicle moving
void STP_DevReg::restrictionChanged()
{
    /*
     * ReferenceSequence:<SequenceName # Version>
     * @datalist:<XX-XX-XX-XX # 0.000>
     */

    NGLogDebug(LogTag_BT_Setup, "[%s] called", __PRETTY_FUNCTION__);

    // notify qml
    emit notifyRestrictionStatus();
}

/*
 * unitTest's usecase
 * UT1: if is restriction
 * UT2: if is not restriction
*/
// get restriction status
bool STP_DevReg::restrictionStatus()
{
    /*
     * ReferenceSequence:<SequenceName # Version>
     * @datalist:<XX-XX-XX-XX # 0.000>
     */

    NGLogDebug(LogTag_BT_Setup, "[%s] called", __PRETTY_FUNCTION__);

    NGLogDebug(LogTag_BT_Setup, "[%s] UICommonInfoFuncInst: %p", __PRETTY_FUNCTION__, UICommonInfoFuncInst);
    if (NULL == UICommonInfoFuncInst) {
        return false;
    }

    // get restriction
    int restric = APP::GetRestriction();

    NGLogDebug(LogTag_BT_Setup,  "[%s] restric is: %d", __PRETTY_FUNCTION__, restric);
    // if is restriction            <- UT1
    if (NGRestrictionStatus_OperationOn == (restric & NGRestrictionStatus_OperationOn)) {
        NGLogDebug(LogTag_BT_Setup,  "[%s] in restriction now", __PRETTY_FUNCTION__);
        // retuen true
        return true;
    }
    // else if is not rectriction           <- UT2
    else {
        NGLogDebug(LogTag_BT_Setup,  "[%s] now not in restriction now", __PRETTY_FUNCTION__);
        // return false
        return false;
    }
}

/// systemLanguageChanged
void STP_DevReg::systemLanguageChanged()
{
    NGLogDebug(LogTag_BT_Setup,  "[%s] called", __PRETTY_FUNCTION__);
    if (NGONSStatus_Closed != GetNGONSAPI()->getONSStatus(MSG_07_09_03_02)) {
        NGLogDebug(LogTag_BT_Setup, "[%s] MSG_07_09_03_02 is not closed ", __PRETTY_FUNCTION__);
        NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingPropertyModelInst is: %p", __PRETTY_FUNCTION__, BtSettingPropertyModelInst);
        if (NULL != BtSettingPropertyModelInst) {
            // get mainPhone name
            QString mainPhone = BtSettingPropertyModelInst->getMainPhoneName();
            NGLogDebug(LogTag_BT_Setup,  "[%s] mainPhone is: %s", __PRETTY_FUNCTION__, mainPhone.toStdString().c_str());
            QString mainName = QString().sprintf(NQResourceManagerInst.getString("MSG_MSG_07_09_03_02_RES_00").toStdString().c_str(), mainPhone.toStdString().c_str());
            NGLogDebug(LogTag_BT_Setup,  "[%s] ONS text is: %s", __PRETTY_FUNCTION__, mainName.toStdString().c_str());

            // add onsContext
            NGONSContext onsContext;
            onsContext.option = NGContextOption_TextList;
            NGONSItemContext context;

            context.type = NGONSItemContextType_RawString;
            context.valueStr = mainName.toStdString();
            onsContext.textList.push_back(context);

            NGButtonRestrictionStatus backBtnRestriction = NGButtonRestrictionStatus_Disable;
            NGButtonRestrictionStatus yesBtnRestriction  = NGButtonRestrictionStatus_Disable;
            NGButtonRestrictionStatus nokBtnRestriction  = NGButtonRestrictionStatus_Disable;
            onsContext.buttonRestrictionStatusList.push_back(backBtnRestriction);
            onsContext.buttonRestrictionStatusList.push_back(yesBtnRestriction);
            onsContext.buttonRestrictionStatusList.push_back(nokBtnRestriction);

            onsContext.specId.specId1 = 6297857;
            onsContext.specId.specId2 = 6297858;
            onsContext.specId.specId3 = 6297859;

            // open ONS
            GetNGONSAPI()->updateONS(MSG_07_09_03_02, onsContext);
        }
    }

    if (NGONSStatus_Closed != GetNGONSAPI()->getONSStatus(MSG_07_09_03_03)) {
        NGLogDebug(LogTag_BT_Setup, "[%s] MSG_07_09_03_02 is not closed ", __PRETTY_FUNCTION__);

        NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingPropertyModelInst is: %p", __PRETTY_FUNCTION__, BtSettingPropertyModelInst);
        if (NULL != BtSettingPropertyModelInst) {
            // get AudioPlayer name
            QString audioPlayer = BtSettingPropertyModelInst->getAudioPlayerName();
            NGLogDebug(LogTag_BT_Setup,  "[%s] audioPlayer is: %s", __PRETTY_FUNCTION__, audioPlayer.toStdString().c_str());
            QString playerName = QString().sprintf(NQResourceManagerInst.getString("MSG_MSG_07_09_03_03_RES_00").toStdString().c_str(), audioPlayer.toStdString().c_str());
            NGLogDebug(LogTag_BT_Setup,  "[%s] ONS text is: %s", __PRETTY_FUNCTION__, playerName.toStdString().c_str());

            // add onsContext
            NGONSContext onsContext;
            onsContext.option = NGContextOption_TextList;
            NGONSItemContext context;

            context.type = NGONSItemContextType_RawString;
            context.valueStr = playerName.toStdString();
            onsContext.textList.push_back(context);

            NGButtonRestrictionStatus backBtnRestriction = NGButtonRestrictionStatus_Disable;
            NGButtonRestrictionStatus yesBtnRestriction  = NGButtonRestrictionStatus_Disable;
            NGButtonRestrictionStatus nokBtnRestriction  = NGButtonRestrictionStatus_Disable;
            onsContext.buttonRestrictionStatusList.push_back(backBtnRestriction);
            onsContext.buttonRestrictionStatusList.push_back(yesBtnRestriction);
            onsContext.buttonRestrictionStatusList.push_back(nokBtnRestriction);

            onsContext.specId.specId1 = 6297885;
            onsContext.specId.specId2 = 6297886;
            onsContext.specId.specId3 = 6297887;

            // open ONS
            GetNGONSAPI()->updateONS(MSG_07_09_03_03, onsContext);
        }
    }

}
/*---------------------------------------------------------------------------*/
// Private functions
/*---------------------------------------------------------------------------*/

/* EOF */
