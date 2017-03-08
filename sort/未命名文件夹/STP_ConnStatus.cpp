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
#include "STP_ConnStatus.h"
#include "BtSetupCommon.h"

// share data
#include "ngapp/AppAPI.h"
#include "UI_ShareDataDef.h"
#include "UI_AppContextDef.h"
#include "UI_TransitionNameID.h"
#include "UICommonInfo/UICommonInfoFunc.h"
#include "UICommonInfo/UICommonInfoPhone.h"

#include "qmlframework/NQImageBase.h"
#include "qmlframework/NQAPI.h"
#include <qmlframework/NQResourceManager.h>

#include "UICC/CC_ListAll_T1_L.h"
#include "UICC/CC_Cmd_Back.h"
#include "UICC/CC_Cmd_T1M1.h"

#include "fnctl/base/FCProxyBase.h"
#include "fnctl/BtSetting/BtSettingInterfaceDef.h"
#include "fnctl/BtSetting/BtSettingDef.h"
#include "fnctl/BtSetting/BtSettingPairedDeviceInfoModel.h"
#include "fnctl/SystemInfo/SystemInfoBTModel.h"
#include "fnctl/BtSetting/BtSettingPairedListModel.h"
#include "fnctl/BtSetting/BtSettingMainDeviceInfoModel.h"
#include "fnctl/BtSetting/BtSettingListModel.h"
#include "fnctl/BtSetting/BtSettingPropertyModel.h"
#include "fnctl/BtHandsfree/BtHandsfreePropertyModel.h"

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
STP_ConnStatus::STP_ConnStatus(QQuickItem *parent)
    : UIMainScreenBase(parent)
    , m_connectBtn(NULL)
    , m_disconnectBtn(NULL)
    , m_hfpImg(NULL)
    , m_hfpBtn(NULL)
    , m_avpImg(NULL)
    , m_avpBtn(NULL)
    , m_subPhoneBtn(NULL)
    , m_devInfoBtn(NULL)
    , m_backBtn(NULL)
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
     * @datalist:<XX-XX-XX-XX # X.XXX>|<YY-YY-YY-YY # Y.YYY>
     */

}

// Destructor
/*
 * unitTest's usecase
 * UT: whether the function execution is completed
*/
STP_ConnStatus::~STP_ConnStatus()
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
void STP_ConnStatus::onCreate()
{
    /*
     * ReferenceSequence:<SequenceName # Version>
     * @datalist:<XX-XX-XX-XX # X.XXX>|<YY-YY-YY-YY # Y.YYY>
     */

    NGLogDebug(LogTag_BT_Setup, "View STP_ConnStatus was created.");

    /*
     * To do something before UIMainScreenBase::onCreate() called.
     */
    // get m_connectBtn
    m_connectBtn = this->findChild<CC_ListAll_T1_L*>("connectBtn");
    NGLogDebug(LogTag_BT_Setup,  "[%s] m_connectBtn is: %p", __PRETTY_FUNCTION__, m_connectBtn);
    // if m_connectBtn is not NULL
    if (NULL != m_connectBtn) {
        NGLogDebug(LogTag_BT_Setup,  "[%s] find child m_connectBtn", __PRETTY_FUNCTION__);
        // connect(m_connectBtn, SIGNAL(buttonClicked(int)), this, SLOT(onConnectBtnClicked()))
        connect(m_connectBtn, SIGNAL(buttonPressed(int)), this, SLOT(onConnectBtnClicked()));
    }

    // get m_disconnectBtn
    m_disconnectBtn = this->findChild<CC_ListAll_T1_L*>("disconnectBtn");
    NGLogDebug(LogTag_BT_Setup,  "[%s] m_disconnectBtn is: %p", __PRETTY_FUNCTION__, m_disconnectBtn);
    // if m_disconnectBtn is not NULL
    if (NULL != m_disconnectBtn) {
        NGLogDebug(LogTag_BT_Setup,  "[%s] find child m_disconnectBtn", __PRETTY_FUNCTION__);
        // connect(m_disconnectBtn, SIGNAL(buttonClicked(int)), this, SLOT(onDisconnectBtnClicked()))
        connect(m_disconnectBtn, SIGNAL(buttonPressed(int)), this, SLOT(onDisconnectBtnClicked()));
    }

    // get m_hfpImg
    m_hfpImg = this->findChild<NQImageBase*>("hpfImg");
    NGLogDebug(LogTag_BT_Setup,  "[%s] m_hfpImg is: %p", __PRETTY_FUNCTION__, m_hfpImg);
    if (NULL == m_hfpImg) {
        NGLogDebug(LogTag_BT_Setup,  "[%s] find child m_hfpImg", __PRETTY_FUNCTION__);
    }

    // get m_hfpBtn
    m_hfpBtn = this->findChild<CC_ListAll_T1_L*>("hfpBtn");
    NGLogDebug(LogTag_BT_Setup,  "[%s] m_hfpBtn is: %p", __PRETTY_FUNCTION__, m_hfpBtn);
    // if m_hfpBtn is not NULL
    if (NULL != m_hfpBtn) {
        NGLogDebug(LogTag_BT_Setup,  "[%s] find child m_hfpBtn", __PRETTY_FUNCTION__);
        // connect(m_hfpBtn, SIGNAL(buttonClicked(int)), this, SLOT(onHfpBtnClicked()));
        connect(m_hfpBtn, SIGNAL(buttonPressed(int)), this, SLOT(onHfpBtnClicked()));
    }

    // get m_avpImg
    m_avpImg = this->findChild<NQImageBase*>("avpImg");
    NGLogDebug(LogTag_BT_Setup,  "[%s] m_avpImg is: %p", __PRETTY_FUNCTION__, m_avpImg);
    if (NULL == m_avpImg) {
        NGLogDebug(LogTag_BT_Setup,  "[%s] find child m_avpImg", __PRETTY_FUNCTION__);
    }

    // get m_avpBtn
    m_avpBtn = this->findChild<CC_ListAll_T1_L*>("avpBtn");
    NGLogDebug(LogTag_BT_Setup,  "[%s] m_avpBtn", __PRETTY_FUNCTION__, m_avpBtn);
    // if m_avpBtn is not NULL
    if (NULL != m_avpBtn) {
        NGLogDebug(LogTag_BT_Setup,  "[%s] find child m_avpBtn", __PRETTY_FUNCTION__);
        // connect(m_avpBtn, SIGNAL(buttonClicked(int)), this, SLOT(onAvpBtnClicked()))
        connect(m_avpBtn, SIGNAL(buttonPressed(int)), this, SLOT(onAvpBtnClicked()));
    }

    // get m_subPhoneBtn
    m_subPhoneBtn = this->findChild<CC_ListAll_T1_L*>("subPhoneBtn");
    NGLogDebug(LogTag_BT_Setup,  "[%s] can not find child m_subPhoneBtn", __PRETTY_FUNCTION__);
    // if m_subPhoneBtn is not NULL
    if (NULL != m_subPhoneBtn) {
        NGLogDebug(LogTag_BT_Setup,  "[%s] find child m_subPhoneBtn", __PRETTY_FUNCTION__);
        // connect(m_subPhoneBtn, SIGNAL(buttonClicked(int)), this, SLOT(onSubPhoneBtnClicked()))
        connect(m_subPhoneBtn, SIGNAL(buttonPressed(int)), this, SLOT(onSubPhoneBtnClicked()));
    }

    // get m_devInfoBtn
    m_devInfoBtn = this->findChild<CC_Cmd_T1M1*>("devInfoBtn");
    NGLogDebug(LogTag_BT_Setup,  "[%s] m_devInfoBtn is: %p", __PRETTY_FUNCTION__, m_devInfoBtn);
    // if m_devInfoBtn is not NULL
    if (NULL != m_devInfoBtn) {
        NGLogDebug(LogTag_BT_Setup,  "[%s] find child m_devInfoBtn", __PRETTY_FUNCTION__);
        // connect(m_devInfoBtn, SIGNAL(buttonClicked(int)), this, SLOT(onDevInfoBtnClicked()))
        connect(m_devInfoBtn, SIGNAL(buttonPressed(int)), this, SLOT(onDevInfoBtnClicked()));
    }

    // get m_backBtn
    m_backBtn = this->findChild<CC_Cmd_Back*>("backBtn");
    NGLogDebug(LogTag_BT_Setup,  "[%s] m_backBtn is: %p", __PRETTY_FUNCTION__, m_backBtn);
    // if NULL is not m_backBtn
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
void STP_ConnStatus::onPreActive()
{
    /*
     * ReferenceSequence:<SequenceName # Version>
     * @datalist:<XX-XX-XX-XX # X.XXX>|<YY-YY-YY-YY # Y.YYY>
     */

    NGLogDebug(LogTag_BT_Setup, "View STP_ConnStatus will be actived.");

    /*
     * To do something before UIMainScreenBase::onPreActive() called.
     */

    m_devName = QString(APP::GetAppContext(PhoneCommonInst->getAppId(), UI_AppContext_Key_STP_ConnStatus_DeviceName).c_str());
    m_addr = QString(APP::GetAppContext(PhoneCommonInst->getAppId(), UI_AppContext_Key_STP_ConnStatus_DeviceMAC).c_str()).toLongLong();
    m_addrStr = QString(APP::GetAppContext(PhoneCommonInst->getAppId(), UI_AppContext_Key_STP_ConnStatus_DeviceAddr).c_str());

    NGLogDebug(LogTag_BT_Setup, "[%s] BtSetupCommonInst: %p", __PRETTY_FUNCTION__, BtSetupCommonInst);
    if (NULL != BtSetupCommonInst) {
        BtSetupCommonInst->notifyTitleChanged(m_devName, BtSetupCommon::ContectType_RawString);
    }

    this->showLog();

    NGLogDebug(LogTag_BT_Setup, "[%s] m_addr is: %llu", __PRETTY_FUNCTION__, m_addr);
    NGLogDebug(LogTag_BT_Setup, "[%s] m_addrStr is: %s", __PRETTY_FUNCTION__, m_addrStr.toStdString().c_str());
    NGLogDebug(LogTag_BT_Setup, "[%s] m_devName is: %s", __PRETTY_FUNCTION__, m_devName.toStdString().c_str());

    // Initialize connect and disconnect button text
    if (NULL != m_connectBtn) {

        QString StrConnect = QString().sprintf(NQResourceManagerInst.getString("STR_MM_07_09_03_RES_00").toStdString().c_str(), m_devName.toStdString().c_str());

        // QString m_text = "Connect ";
        // m_connectBtn->setText(m_text.append(m_devName));
        m_connectBtn->setText(StrConnect);
        NGLogDebug(LogTag_BT_Setup, "[%s] initialize connect btn text", __PRETTY_FUNCTION__);
    }
    if (NULL != m_disconnectBtn) {

        QString StrDisconnect = QString().sprintf(NQResourceManagerInst.getString("STR_MM_07_09_03_RES_01").toStdString().c_str(), m_devName.toStdString().c_str());

        // QString m_text = "Disconnect ";
        // m_disconnectBtn->setText(m_text.append(m_devName));
        m_disconnectBtn->setText(StrDisconnect);
        NGLogDebug(LogTag_BT_Setup, "[%s] initialize disconnect btn text", __PRETTY_FUNCTION__);
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
    NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingFcProxyInst is: %p", __PRETTY_FUNCTION__, BtSettingFcProxyInst);
    // if (BtSettingFcProxyInst is not NULL)
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

    emit notifyDevCountChanged();

    m_connectBtn->setStyleId("F02");
    m_disconnectBtn->setStyleId("F02");

    if (isBlinkresetRestored()) {
        // set FC DevName and BtAddr
        if (NULL != BtSettingFcProxyInst) {
            QMap<QString, QVariant> qmap;
            qmap.insert(FC_BT_SETTING_PAR_KEY_ADDRESS, m_addr);
            emit request(FC_BT_SETTING_REQ_GET_PAIRED_DEVICE_INFO_FROM_LIST_MODEL, QVariant(qmap));
            NGLogDebug(LogTag_BT_Setup, "[%s] request FC Device info", __PRETTY_FUNCTION__);
        }
    }

     bool isSubPhone = BtSettingPairedDeviceInfoModelInst->isSubPhoneSeleted();
     NGLogDebug(LogTag_BT_Setup,  "[%s] isSubPhone is: %d", __PRETTY_FUNCTION__, isSubPhone);
     bool isMainPhone = BtSettingPairedDeviceInfoModelInst->isMainPhoneSelected();
     NGLogDebug(LogTag_BT_Setup,  "[%s] isMainPhone is: %d", __PRETTY_FUNCTION__, isMainPhone);

    UIMainScreenBase::onPreActive();
}

// onActive
/*
 * unitTest's usecase
 * UT: whether the function execution is completed
*/
void STP_ConnStatus::onActive()
{
    /*
     * ReferenceSequence:<SequenceName # Version>
     * @datalist:<XX-XX-XX-XX # X.XXX>|<YY-YY-YY-YY # Y.YYY>
     */

    NGLogDebug(LogTag_BT_Setup, "View STP_ConnStatus did actived.");

    /*
     * To do something before UIMainScreenBase::onActive() called.
     */

    UIMainScreenBase::onActive();
}

// onPreDeactive
/*
 * unitTest's usecase
 * UT1: whether the MSG_07_09_03_00 is opened
 * UT2: whether the MSG_07_09_03_01 is opened
 * UT3: whether the MSG_07_09_03_02 is opened
 * UT5: whether the MSG_07_09_03_03 is opened
 * UT6: whether the MSG_07_09_03_04 is opened
 * UT7: whether the MSG_10_01_28_02 is opened
*/
void STP_ConnStatus::onPreDeactive()
{
    /*
     * ReferenceSequence:<SequenceName # Version>
     * @datalist:<XX-XX-XX-XX # X.XXX>|<YY-YY-YY-YY # Y.YYY>
     */

    NGLogDebug(LogTag_BT_Setup, "View STP_ConnStatus will be deactived.");

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
    GetNGONSAPI()->unregistCallbackByOnsId(MSG_07_09_03_00);
    GetNGONSAPI()->closeONS(MSG_07_09_03_00);
    NGLogDebug(LogTag_BT_Setup, "[%s] close MSG_07_09_03_00", __PRETTY_FUNCTION__);

    GetNGONSAPI()->unregistCallbackByOnsId(MSG_07_09_03_01);
    GetNGONSAPI()->closeONS(MSG_07_09_03_01);
    NGLogDebug(LogTag_BT_Setup, "[%s] close MSG_07_09_03_01", __PRETTY_FUNCTION__);

    GetNGONSAPI()->unregistCallbackByOnsId(MSG_07_09_03_02);
    GetNGONSAPI()->closeONS(MSG_07_09_03_02);
    NGLogDebug(LogTag_BT_Setup, "[%s] close MSG_07_09_03_02", __PRETTY_FUNCTION__);

    GetNGONSAPI()->unregistCallbackByOnsId(MSG_07_09_03_03);
    GetNGONSAPI()->closeONS(MSG_07_09_03_03);
    NGLogDebug(LogTag_BT_Setup, "[%s] close MSG_07_09_03_03", __PRETTY_FUNCTION__);

    GetNGONSAPI()->unregistCallbackByOnsId(MSG_07_09_03_04);
    GetNGONSAPI()->closeONS(MSG_07_09_03_04);
    NGLogDebug(LogTag_BT_Setup, "[%s] close MSG_07_09_03_04", __PRETTY_FUNCTION__);

    GetNGONSAPI()->unregistCallbackByOnsId(MSG_10_01_28_02);
    GetNGONSAPI()->closeONS(MSG_10_01_28_02);
    NGLogDebug(LogTag_BT_Setup, "[%s] close MSG_10_01_28_02", __PRETTY_FUNCTION__);

    NGLogDebug(LogTag_BT_Setup, "[%s] all ONS is closed", __PRETTY_FUNCTION__);

    UIMainScreenBase::onPreDeactive();
}

// onDeactive
/*
 * unitTest's usecase
 * UT: whether the function execution is completed
*/
void STP_ConnStatus::onDeactive()
{
    /*
     * ReferenceSequence:<SequenceName # Version>
     * @datalist:<XX-XX-XX-XX # X.XXX>|<YY-YY-YY-YY # Y.YYY>
     */

    NGLogDebug(LogTag_BT_Setup, "View STP_ConnStatus did deactived.");

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
void STP_ConnStatus::onDestroy()
{
    /*
     * ReferenceSequence:<SequenceName # Version>
     * @datalist:<XX-XX-XX-XX # X.XXX>|<YY-YY-YY-YY # Y.YYY>
     */

    NGLogDebug(LogTag_BT_Setup, "View STP_ConnStatus will be destroyed.");

    /*
     * To do something before UIMainScreenBase::onDestroy() called.
     */
    // disconnect m_connectBtn
    // if m_connectBtn is not NULL
    if (NULL != m_connectBtn) {
        // disconnect(m_connectBtn, SIGNAL(buttonClicked(int)), this, SLOT(onConnectBtnClicked()))
        disconnect(m_connectBtn, SIGNAL(buttonPressed(int)), this, SLOT(onConnectBtnClicked()));
    }
    m_connectBtn = NULL;

    // disconnect m_disconnectBtn
    // if m_disconnectBtnis not NULL
    if (NULL != m_disconnectBtn) {
        // disconnect(m_disconnectBtn, SIGNAL(buttonClicked(int)), this, SLOT(onDisconnectBtnClicked()))
        disconnect(m_disconnectBtn, SIGNAL(buttonPressed(int)), this, SLOT(onDisconnectBtnClicked()));
    }
    m_disconnectBtn = NULL;

    // disconnect m_hfpBtn
    // if m_hfpBtn is not NULL
    if (NULL != m_hfpBtn) {
        // disconnect(m_hfpBtn, SIGNAL(buttonClicked(int)), this, SLOT(onHfpBtnClicked()))
        disconnect(m_hfpBtn, SIGNAL(buttonPressed(int)), this, SLOT(onHfpBtnClicked()));
    }
    m_hfpBtn = NULL;

    // disconnect m_hfpImg
    m_hfpImg = NULL;

    // disconnect m_avpBtn
    // if m_avpBtn is not NULL
    if (NULL != m_avpBtn) {
        // disconnect(m_avpBtn, SIGNAL(buttonClicked(int)), this, SLOT(onAvpBtnClicked()))
        disconnect(m_avpBtn, SIGNAL(buttonPressed(int)), this, SLOT(onAvpBtnClicked()));
    }
    m_avpBtn = NULL;

    // disconnect m_avpImg
    m_avpImg = NULL;

    // disconnect m_subPhoneBtn
    // if m_subPhoneBtn is not NULL
    if (NULL != m_subPhoneBtn) {
        // disconnect(m_subPhoneBtn, SIGNAL(buttonClicked(int)), this, SLOT(onSubPhoneBtnClicked()))
        disconnect(m_subPhoneBtn, SIGNAL(buttonPressed(int)), this, SLOT(onSubPhoneBtnClicked()));
    }
    m_subPhoneBtn = NULL;

    // disconnect m_devInfoBtn
    // if m_devInfoBtn is not NULL
    if (NULL != m_devInfoBtn) {
        // disconnect(m_devInfoBtn, SIGNAL(buttonClicked(int)), this, SLOT(onDevInfoBtnClicked()))
        disconnect(m_devInfoBtn, SIGNAL(buttonPressed(int)), this, SLOT(onDevInfoBtnClicked()));
    }
    m_devInfoBtn = NULL;

    // disconnect m_backBtn
    // if m_backBtn is not NULL
    if (NULL != m_backBtn) {
        // disconnect(m_backBtn, SIGNAL(buttonClicked(int)), this, SLOT(onBackBtnClicked()))
        disconnect(m_backBtn, SIGNAL(buttonPressed(int)), this, SLOT(onBackBtnClicked()));
    }
    m_backBtn = NULL;

    m_addr = 0;

    m_otherAddr = 0;

    m_devName = "";

    m_addrStr = "";

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

/*
 * unitTest's usecase
 * UT: whether the function execution is completed
*/
// transfer to connecting
void STP_ConnStatus::transferToConnecting (const BtSetupCommon::DevType devType)
{
    /*
  * ReferenceSequence:<SequenceName # Version>
  * @datalist:<XX-XX-XX-XX # 0.000>
  */

    // save shareData
    NGLogDebug(LogTag_BT_Setup, "[%s] UICommonInfoPhoneInst: %p", __PRETTY_FUNCTION__, UICommonInfoPhoneInst);
    if (NULL != UICommonInfoPhoneInst) {
        UICommonInfoPhoneInst->setDeviceInfo(m_addr, m_addrStr, m_devName);
    }

    // get TransFrom Val
    std::string from = APP::GetShareDataStr(UI_ShareData_Key_TransFrom);
    NGLogDebug(LogTag_BT_Setup, "[%s] valueTransFrom: %s", __PRETTY_FUNCTION__, from.c_str());
    // if transFrom is Devreg or subPhonesetting or BtSetting or SetupAppBluetooth or SetupAppPhone         <-UT1
    if ((UI_ShareData_Value_TransFrom_Str_DevReg == from)\
            || (UI_ShareData_Value_TransFrom_Str_SubPhoneSetting == from)\
            || (UI_ShareData_Value_TransFrom_Str_BtSetting == from)\
            || (UI_ShareData_Value_TransFrom_Str_SetupAppBluetooth == from)\
            || (UI_ShareData_Value_TransFrom_Str_SetupAppPhone == from)\
            || (UI_ShareData_Value_Str_Invalid == from)\
            || (UI_ShareData_Value_TransFrom_Str_DevReplace == from)\
            || (UI_ShareData_Value_Str_PhoneAddNew == from)\
            || (UI_ShareData_Value_Str_AudioAddNew == from)) {
        // set transFrom in shareData is ConnStatus
        APP::SetShareDataStr(UI_ShareData_Key_TransFrom, UI_ShareData_Value_TransFrom_Str_ConnStatus);
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
 * UT5: if ONSId is MSG_07_09_03_04
 * UT6: if ONSId is MSG_10_01_28_02
 * UT7: if ONSId is error
*/
void STP_ConnStatus::openONSWithIdAndContext(int ONSId)
{
    /*
  * ReferenceSequence:<SequenceName # Version>
  * @datalist:<XX-XX-XX-XX # X.XXX>|<YY-YY-YY-YY # Y.YYY>
  */

    NGLogDebug(LogTag_BT_Setup, "[%s] openONSWithIdAndContext() called", __PRETTY_FUNCTION__);

    // if ONSId is MSG_07_09_03_00          <-UT1
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

        onsContext.specId.specId1 = 6297857;
        onsContext.specId.specId2 = 6297858;
        onsContext.specId.specId3 = 6297859;

        // open ONS
        GetNGONSAPI()->openONS(ONSId, onsContext, *this);
    }
    // else if ONSId is MSG_07_09_03_01          <-UT2
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
    // else if ONSId is MSG_07_09_03_02          <-UT3
    else if (MSG_07_09_03_02 == ONSId) {
        NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingPropertyModelInst is: %p", __PRETTY_FUNCTION__, BtSettingPropertyModelInst);
        if (NULL != BtSettingPropertyModelInst) {
            // get mainPhone name
            QString mainPhone = BtSettingPropertyModelInst->getMainPhoneName();
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

            onsContext.specId.specId1 = 6298113;
            onsContext.specId.specId2 = 6298114;
            onsContext.specId.specId3 = 6298115;

            // open ONS
            GetNGONSAPI()->openONS(ONSId, onsContext, *this);
        }
    }
    // else if ONSId is MSG_07_09_03_03          <-UT4
    else if (MSG_07_09_03_03 == ONSId) {
        NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingPropertyModelInst is: %p", __PRETTY_FUNCTION__, BtSettingPropertyModelInst);
        if (NULL != BtSettingPropertyModelInst) {
            // get AudioPlayer name
            QString audioPlayer = BtSettingPropertyModelInst->getAudioPlayerName();
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

            onsContext.specId.specId1 = 6298241;
            onsContext.specId.specId2 = 6298242;
            onsContext.specId.specId3 = 6298243;

            // open ONS
            GetNGONSAPI()->openONS(ONSId, onsContext, *this);
        }
    }
    // else if ONSId is MSG_07_09_03_04          <-UT5
    else if (MSG_07_09_03_04 == ONSId) {
        // add onsContext
        NGONSContext onsContext;
        NGONSItemContext context;

        context.type = NGONSItemContextType_StringId;
        context.valueStr = std::string("MSG_MSG_07_09_03_04_RES_00");
        onsContext.textList.push_back(context);

        NGButtonRestrictionStatus backBtnRestriction = NGButtonRestrictionStatus_Disable;
        NGButtonRestrictionStatus yesBtnRestriction  = NGButtonRestrictionStatus_Disable;
        NGButtonRestrictionStatus nokBtnRestriction  = NGButtonRestrictionStatus_Disable;
        onsContext.buttonRestrictionStatusList.push_back(backBtnRestriction);
        onsContext.buttonRestrictionStatusList.push_back(yesBtnRestriction);
        onsContext.buttonRestrictionStatusList.push_back(nokBtnRestriction);

        onsContext.specId.specId1 = 6298369;
        onsContext.specId.specId2 = 6298370;
        onsContext.specId.specId3 = 6298371;

        // open ONS
        GetNGONSAPI()->openONS(ONSId, onsContext, *this);
    }
    // else if ONSId is MSG_10_01_28_02          <-UT6
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

        onsContext.specId.specId1 = 6298497;
        onsContext.specId.specId2 = 6298498;

        // open ONS
        GetNGONSAPI()->openONS(ONSId, onsContext, *this);
    }
    // else if ONSId is error           <-UT7
    else {
        NGLogDebug(LogTag_BT_Setup, "[%s] ONSId error", __PRETTY_FUNCTION__);
    }

    // init OnsStstus
    initOnsStatus();
}

/*
 * unitTest's usecase
 * UT1: UT: whether the function execution is completed
*/
// get device count
quint32 STP_ConnStatus::getDeviceCount()
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<XX-XX-XX-XX # X.XXX>|<YY-YY-YY-YY # Y.YYY>
    */

    NGLogDebug(LogTag_BT_Setup, "[%s] called", __PRETTY_FUNCTION__);

    NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingListModelInst: %p", __PRETTY_FUNCTION__, BtSettingListModelInst);
    if (NULL == BtSettingListModelInst) {
        return -1;
    }

    NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingPairedListModelInst: %p", __PRETTY_FUNCTION__, BtSettingListModelInst->getPairedListModel());
    if (NULL == BtSettingListModelInst->getPairedListModel()) {
        return -1;
    }

    // FC: get(number of paired devices)            <- UT1
    quint32 devCount = BtSettingListModelInst->getPairedListModel()->getDeviceCount();
    NGLogDebug(LogTag_BT_Setup, "[%s] devCount: %d", __PRETTY_FUNCTION__, devCount);

    return devCount;
}

/*---------------------------------------------------------------------------*/
// Public slots functions
/*---------------------------------------------------------------------------*/

// click Connect button
/*
 * unitTest's usecase
 * UT1: if region is OCeania and HFP is not Available, this device support AVP, any other device has connected AVP
 * UT2: if region is OCeania and HFP is not Available, this device support AVP, any other device has not connected AVP
 * UT3: if region is OCeania and HFP is not Available, this device does not support AVP
 * UT4: if region is OCeania and HFP is Available, any other device has connected HFP or AVP
 * UT5: if region is OCeania and HFP is Available, other device has not connected HFP or AVP, this device support HFP
 * UT6: if region is OCeania and HFP is Available, other device has not connected HFP or AVP, this device does not support HFP
 * UT7: if region is EU or China, data is communicating
 * UT8: if region is EU or China, data is not communicating, any other device has connected HFP or AVP
 * UT9: if region is EU or China, data is not communicating, other device has not connected HFP or AVP, this device support HFP
 * UT10: if region is EU or China, data is not communicating, other device has not connected HFP or AVP, this device does not support HFP
 * UT11: if other region, any other device has connected HFP or AVP
 * UT12: if other region, other device has not connected HFP or AVP, this device support HFP
 * UT13: if other region, other device has not connected HFP or AVP, this device does not support HFP
*/
void STP_ConnStatus::onConnectBtnClicked()
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

    m_profFlag = BtSetupCommon::DevType_All;

    bool isOceania = PhoneCommon::GetInstance()->getUICFunc()->kindPNR().isRegion_OCEANIA();
    bool isEU = PhoneCommon::GetInstance()->getUICFunc()->kindPNR().isRegion_EU();
    bool isChina = PhoneCommon::GetInstance()->getUICFunc()->kindPNR().isRegion_CHINA();

    NGLogDebug(LogTag_BT_Setup,  "[%s] isOceania is: %d", __PRETTY_FUNCTION__, isOceania);
    NGLogDebug(LogTag_BT_Setup,  "[%s] isEU is: %d", __PRETTY_FUNCTION__, isEU);
    NGLogDebug(LogTag_BT_Setup,  "[%s] isChina is: %d", __PRETTY_FUNCTION__, isChina);

    // if region is OCeania
    if (isOceania) {
        // if HFP is not Available
        if (!(BtSettingPropertyModelInst->isHFPAvailable())) {
            NGLogDebug(LogTag_BT_Setup,  "[%s] the HFP is not available", __PRETTY_FUNCTION__);
            // if this device support AVP
            if (BtSettingPairedDeviceInfoModelInst->isSupportAVP()) {
                NGLogDebug(LogTag_BT_Setup,  "[%s] this device support AVP", __PRETTY_FUNCTION__);

                bool anyAvpConnected = false;
                if (BtSettingPropertyModelInst->getAvpConnectedStatus()) {
                    anyAvpConnected = true;
                }

                bool thisDeviceConnectedAvp = BtSettingPairedDeviceInfoModelInst->isAVPConnected();

                // if any other device has connected AVP            <- UT1
                if (anyAvpConnected && (!thisDeviceConnectedAvp)) {
                    // open MSG_07_09_03_04
                    NGLogDebug(LogTag_BT_Setup, "[%s] other device has connected AVP", __PRETTY_FUNCTION__);
                    this->openONSWithIdAndContext(MSG_07_09_03_04);
                }
                // else if other device has not connected AVP       <- UT2
                else {
                    NGLogDebug(LogTag_BT_Setup,  "[%s] HFP is not available but other device has not connected AVP", __PRETTY_FUNCTION__);
                    // ScreenTransfer STP_profConnecting (connect as main phone)
                    this->transferToConnecting(BtSetupCommon::DevType_Audio);
                }
            }
            // else if this device does not support AVP         <- UT3
            else {
                // open MSG_10_01_28_02
                NGLogDebug(LogTag_BT_Setup, "[%s] HFP is not available and this device does not support AVP", __PRETTY_FUNCTION__);
                this->openONSWithIdAndContext(MSG_10_01_28_02);
            }
        }
        // else if HFP is available
        else {
            NGLogDebug(LogTag_BT_Setup,  "[%s] HFP is available", __PRETTY_FUNCTION__);
            // HFP status
            bool anyHfpConnected = false;
            if (BtSettingPropertyModelInst->getHfpConnectedStatus()) {
                anyHfpConnected = true;
            }

            bool thisDeviceConnectedHfp = BtSettingPairedDeviceInfoModelInst->isHFPConnected();

            // AVP status
            bool anyAvpConnected = false;
            if (BtSettingPropertyModelInst->getAvpConnectedStatus()) {
                anyAvpConnected = true;
            }

            bool thisDeviceConnectedAvp = BtSettingPairedDeviceInfoModelInst->isAVPConnected();

            // if any other device has connected HFP or AVP         <- UT4
            if (((!thisDeviceConnectedHfp) && anyHfpConnected) || ((!thisDeviceConnectedAvp) && anyAvpConnected)) {
                NGLogDebug(LogTag_BT_Setup,  "[%s] other device has connected HFP or AVP", __PRETTY_FUNCTION__);
                // open MSG_07_09_03_04
                this->openONSWithIdAndContext(MSG_07_09_03_04);
            }
            // else if other device has not connected HFP or AVP
            else {
                // if this device support HFP           <- UT5
                if (BtSettingPairedDeviceInfoModelInst->isSupportHFP()) {
                    NGLogDebug(LogTag_BT_Setup,  "[%s] any other Device has not connected, this device support HFP", __PRETTY_FUNCTION__);
                    // ScreenTransfer STP_profConnecting (connect all)
                    NGLogDebug(LogTag_BT_Setup, "[%s] readly to transfer to Connect ALL", __PRETTY_FUNCTION__);
                    this->transferToConnecting(BtSetupCommon::DevType_All);
                }
                // else if this device does not support HFP         <- UT6
                else {
                    NGLogDebug(LogTag_BT_Setup,  "[%s] any other Device has not connected, this device does not support HFP", __PRETTY_FUNCTION__);
                    // ScreenTransfer STP_profConnecting (connect Audio)
                    NGLogDebug(LogTag_BT_Setup, "[%s] readly to transfer to Connect Audio", __PRETTY_FUNCTION__);
                    this->transferToConnecting(BtSetupCommon::DevType_Audio);
                }
            }
        }
    }
    // else if region is EU or China
    else if (isEU || isChina) {
        // if data is communicating         <- UT7
        if (BtSettingPropertyModelInst->isDataCommunication()) {
            NGLogDebug(LogTag_BT_Setup,  "[%s] data is communicating", __PRETTY_FUNCTION__);
            // open ONS to stop data communicating
            this->openONSWithIdAndContext(MSG_07_09_03_00);
        }
        // else if data is not communicating
        else {
            NGLogDebug(LogTag_BT_Setup,  "[%s] data is not communicating", __PRETTY_FUNCTION__);
            // HFP status
            bool anyHfpConnected = false;
            if (BtSettingPropertyModelInst->getHfpConnectedStatus()) {
                anyHfpConnected = true;
            }

            bool thisDeviceConnectedHfp = BtSettingPairedDeviceInfoModelInst->isHFPConnected();

            // AVP status
            bool anyAvpConnected = false;
            if (BtSettingPropertyModelInst->getAvpConnectedStatus()) {
                anyAvpConnected = true;
            }

            bool thisDeviceConnectedAvp = BtSettingPairedDeviceInfoModelInst->isAVPConnected();

            // if any other device has connected HFP or AVP         <-UT8
            if (((!thisDeviceConnectedHfp) && anyHfpConnected) || ((!thisDeviceConnectedAvp) && anyAvpConnected)) {
                NGLogDebug(LogTag_BT_Setup,  "[%s] other device has connected HFP or AVP", __PRETTY_FUNCTION__);
                // open MSG_07_09_03_04
                this->openONSWithIdAndContext(MSG_07_09_03_04);
            }
            // else if other device has not connected HFP or AVP
            else {
                // if this device support HFP           <- UT9
                if (BtSettingPairedDeviceInfoModelInst->isSupportHFP()) {
                    NGLogDebug(LogTag_BT_Setup,  "[%s] any other Device has not connected, this device support HFP", __PRETTY_FUNCTION__);
                    // ScreenTransfer STP_profConnecting (connect all)
                    NGLogDebug(LogTag_BT_Setup, "[%s] readly to transfer to Connect ALL", __PRETTY_FUNCTION__);
                    this->transferToConnecting(BtSetupCommon::DevType_All);
                }
                // else if this device does not support HFP         <-UT10
                else {
                    NGLogDebug(LogTag_BT_Setup,  "[%s] any other Device has not connected, this device does not support HFP", __PRETTY_FUNCTION__);
                    // ScreenTransfer STP_profConnecting (connect Audio)
                    NGLogDebug(LogTag_BT_Setup, "[%s] readly to transfer to Connect Audio", __PRETTY_FUNCTION__);
                    this->transferToConnecting(BtSetupCommon::DevType_Audio);
                }
            }
        }
    }
    // else if other region
    else {
        bool anyHfpConnected = false;
        if (BtSettingPropertyModelInst->getHfpConnectedStatus()) {
            anyHfpConnected = true;
        }

        bool thisDeviceConnectedHfp = BtSettingPairedDeviceInfoModelInst->isHFPConnected();

        // AVP status
        bool anyAvpConnected = false;
        if (BtSettingPropertyModelInst->getAvpConnectedStatus()) {
            anyAvpConnected = true;
        }

        bool thisDeviceConnectedAvp = BtSettingPairedDeviceInfoModelInst->isAVPConnected();

        // if any other device has connected HFP or AVP         <-UT11
        if (((!thisDeviceConnectedHfp) && anyHfpConnected) || ((!thisDeviceConnectedAvp) && anyAvpConnected)) {
            NGLogDebug(LogTag_BT_Setup,  "[%s] other device has connected HFP or AVP", __PRETTY_FUNCTION__);
            // open MSG_07_09_03_04
            this->openONSWithIdAndContext(MSG_07_09_03_04);
        }
        // else if other device has not connected HFP or AVP
        else {
            // if this device support HFP           <-UT12
            if (BtSettingPairedDeviceInfoModelInst->isSupportHFP()) {
                NGLogDebug(LogTag_BT_Setup,  "[%s] any other Device has not connected, this device support HFP", __PRETTY_FUNCTION__);
                // ScreenTransfer STP_profConnecting (connect all)
                NGLogDebug(LogTag_BT_Setup, "[%s] readly to transfer to Connect ALL", __PRETTY_FUNCTION__);
                this->transferToConnecting(BtSetupCommon::DevType_All);
            }
            // else if this device does not support HFP         <-UT13
            else {
                NGLogDebug(LogTag_BT_Setup,  "[%s] any other Device has not connected, this device does not support HFP", __PRETTY_FUNCTION__);
                // ScreenTransfer STP_profConnecting (connect Audio)
                NGLogDebug(LogTag_BT_Setup, "[%s] readly to transfer to Connect Audio", __PRETTY_FUNCTION__);
                this->transferToConnecting(BtSetupCommon::DevType_Audio);
            }
        }
    }
}

/*
 * unitTest's usecase
 * UT1: UT: whether the function execution is completed
*/
// click Disconnect button
void STP_ConnStatus::onDisconnectBtnClicked()
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<seq_DisconnectDevice # 1.01>
    */

    if (NULL == BtSettingFcProxyInst) {
        NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingFcProxyInst is NULL", __PRETTY_FUNCTION__);
        return;
    }

    if (NULL == BtSettingPairedDeviceInfoModelInst) {
        NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingPairedDeviceInfoModelInst is NULL", __PRETTY_FUNCTION__);
        return;
    }

    QMap<QString, QVariant> qmap;
    qmap.insert(FC_BT_SETTING_PAR_KEY_ADDRESS, m_addr);
    // quint32 m_profile = BtSettingPairedDeviceInfoModelInst->getDeviceType();
    quint32 m_profile = BtSetting_DeviceType_MainPhone | BtSetting_DeviceType_AudioPlayer | BtSetting_DeviceType_SubPhone;
    NGLogDebug(LogTag_BT_Setup,  "[%s] request disconnect type is: %d", __PRETTY_FUNCTION__, m_profile);
    qmap.insert(FC_BT_SETTING_PAR_KEY_DEVICE_TYPE, m_profile);
    emit request(FC_BT_SETTING_REQ_DISCONNECT_DEVICE_TYPE, QVariant(qmap));
    NGLogDebug(LogTag_BT_Setup, "[%s] Request FC disconnect device: %llu", __PRETTY_FUNCTION__, m_addr);
}

/*
 * unitTest's usecase
 * UT1: if HFP is connected, this device is subPhone
 * UT2: if HFP is connected, this device is not subPhone
 * UT3: if HFP is not connected, is Oceania, HFP is not available
 * UT4: if HFP is not connected, is Oceania, HFP is available, main HFP has connected
 * UT5: if HFP is not connected, is Oceania, HFP is available, main HFP has not connected
 * UT6: if HFP is not connected, is EU and China, data is communicating
 * UT7: if HFP is not connected, is EU and China, data is not communicating, main HFP has connected
 * UT8: if HFP is not connected, is EU and China, data is not communicating, main HFP has not connected
 * UT9: if HFP is not connected, is other region, main HFP has connected
 * UT10: if HFP is not connected, is other region, main HFP has not connected
*/
// click HFP button
void STP_ConnStatus::onHfpBtnClicked()
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<seq_ConnectDevice # 1.01>
    */

    NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingPropertyModelInst is: %p", __PRETTY_FUNCTION__, BtSettingPropertyModelInst);
    if (NULL == BtSettingPropertyModelInst) {
        return;
    }
    NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingPairedDeviceInfoModelInst is: %p", __PRETTY_FUNCTION__, BtSettingPairedDeviceInfoModelInst);
    if (NULL == BtSettingPairedDeviceInfoModelInst) {
        return;
    }

    if (NULL != BtSettingPairedDeviceInfoModelInst) {
        //  if HFP is connected
        if (BtSetting_ProfileId_HFP & (BtSettingPairedDeviceInfoModelInst->getConnectedFunction())) {
            if (NULL != BtSettingFcProxyInst) {
                // if this device is subPhone           <- UT1
                if ((BtSettingPairedDeviceInfoModelInst->getDeviceType()) & BtSetting_DeviceType_SubPhone) {
                    // request FC to disconnect subPhone
                    QMap<QString, QVariant> qmap;
                    qmap.insert(FC_BT_SETTING_PAR_KEY_ADDRESS, m_addr);
                    qint16 m_profile = BtSetting_DeviceType_SubPhone;
                    qmap.insert(FC_BT_SETTING_PAR_KEY_DEVICE_TYPE, m_profile);
                    emit request(FC_BT_SETTING_REQ_DISCONNECT_DEVICE_TYPE, QVariant(qmap));
                    NGLogDebug(LogTag_BT_Setup, "[%s] Request FC disconnectAsPhone device: %llu", __PRETTY_FUNCTION__, m_addr);
                }
                // if this device is not subPhone       <- UT2
                else {
                    // request FC to disconnect mainPhone
                    QMap<QString, QVariant> qmap;
                    qmap.insert(FC_BT_SETTING_PAR_KEY_ADDRESS, m_addr);
                    qint16 m_profile = BtSetting_DeviceType_MainPhone;
                    qmap.insert(FC_BT_SETTING_PAR_KEY_DEVICE_TYPE, m_profile);
                    emit request(FC_BT_SETTING_REQ_DISCONNECT_DEVICE_TYPE, QVariant(qmap));
                    NGLogDebug(LogTag_BT_Setup, "[%s] Request FC disconnectAsPhone device: %llu", __PRETTY_FUNCTION__, m_addr);
                }
            }
        }
        // if HFP is not connected
        else {

            m_profFlag = BtSetupCommon::DevType_MainPhone;

            bool isOceania = PhoneCommon::GetInstance()->getUICFunc()->kindPNR().isRegion_OCEANIA();
            bool isEU = PhoneCommon::GetInstance()->getUICFunc()->kindPNR().isRegion_EU();
            bool isChina = PhoneCommon::GetInstance()->getUICFunc()->kindPNR().isRegion_CHINA();

            NGLogDebug(LogTag_BT_Setup,  "[%s] isOceania is: %d", __PRETTY_FUNCTION__, isOceania);
            NGLogDebug(LogTag_BT_Setup,  "[%s] isEU is: %d", __PRETTY_FUNCTION__, isEU);
            NGLogDebug(LogTag_BT_Setup,  "[%s] isChina is: %d", __PRETTY_FUNCTION__, isChina);

            // if is Oceania
            if (isOceania) {
                // if HFP is not available          <- UT3
                if (!(BtSettingPropertyModelInst->isHFPAvailable())) {
                    // open ONS HFP is not Available
                    NGLogDebug(LogTag_BT_Setup, "[%s] readly to open MSG_10_01_28_02", __PRETTY_FUNCTION__);
                    this->openONSWithIdAndContext(MSG_10_01_28_02);
                }
                // else if HFP is available
                else {
                    // if main HFP has connected        <- UT4
                    if (BtSettingPropertyModelInst->getHfpConnectedStatus()) {
                        // open ONS to stop other main HFP
                        NGLogDebug(LogTag_BT_Setup, "[%s] readly to open MSG_07_09_03_02", __PRETTY_FUNCTION__);
                        this->openONSWithIdAndContext(MSG_07_09_03_02);
                    }
                    // else if main HFP has not connected       <- UT5
                    else {
                        NGLogDebug(LogTag_BT_Setup, "[%s] readly to ScreenTransfer", __PRETTY_FUNCTION__);
                        // ScreenTransfer STP_profConnecting (connect as main phone)
                        this->transferToConnecting(BtSetupCommon::DevType_MainPhone);
                    }
                }
            }
            // else if EU and China
            else if (isEU || isChina) {
                // if data is communicating         <- UT6
                if (BtSettingPropertyModelInst->isDataCommunication()) {
                    NGLogDebug(LogTag_BT_Setup,  "[%s] the data is communicating", __PRETTY_FUNCTION__);
                    // open ONS to stop data communicating
                    this->openONSWithIdAndContext(MSG_07_09_03_00);
                }
                // else if data is not communicating
                else {
                    // if main HFP has connected            <- UT7
                    if (BtSettingPropertyModelInst->getHfpConnectedStatus()) {
                        // open ONS to stop other main HFP
                        NGLogDebug(LogTag_BT_Setup, "[%s] readly to open MSG_07_09_03_02", __PRETTY_FUNCTION__);
                        this->openONSWithIdAndContext(MSG_07_09_03_02);
                    }
                    // else if main HFP has not connected           <- UT8
                    else {
                        NGLogDebug(LogTag_BT_Setup, "[%s] readly to ScreenTransfer", __PRETTY_FUNCTION__);
                        // ScreenTransfer STP_profConnecting (connect as main phone)
                        this->transferToConnecting(BtSetupCommon::DevType_MainPhone);
                    }
                }
            }
            // else if other region
            else {
                // if main HFP has connected            <-UT9
                if (BtSettingPropertyModelInst->getHfpConnectedStatus()) {
                    // open ONS to stop other main HFP
                    NGLogDebug(LogTag_BT_Setup, "[%s] readly to open MSG_07_09_03_02", __PRETTY_FUNCTION__);
                    this->openONSWithIdAndContext(MSG_07_09_03_02);
                }
                // else if main HFP has not connected           <- UT10
                else {
                    NGLogDebug(LogTag_BT_Setup, "[%s] readly to ScreenTransfer", __PRETTY_FUNCTION__);
                    // ScreenTransfer STP_profConnecting (connect as main phone)
                    this->transferToConnecting(BtSetupCommon::DevType_MainPhone);
                }
            }
        }
    }
}

// click AVP button
/*
 * unitTest's usecase
 * UT1: if AVP is connected
 * UT2: if AVP is not connected, is EU and China, data is communicating
 * UT3: if AVP is not connected, is EU and China, data is not communicating, other device has connected AVP
 * UT4: if AVP is not connected, is EU and China, data is not communicating, other device has not connected AVP
 * UT5: if AVP is not connected, region is other, other device has connected AVP
 * UT6: if AVP is not connected, region is other, other device has not connected AVP
*/
void STP_ConnStatus::onAvpBtnClicked()
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<seq_ConnectDevice # 1.01>
    */

    NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingPropertyModelInst is: %p", __PRETTY_FUNCTION__, BtSettingPropertyModelInst);
    if (NULL == BtSettingPropertyModelInst) {
        return;
    }
    NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingPairedDeviceInfoModelInst is: %p", __PRETTY_FUNCTION__, BtSettingPairedDeviceInfoModelInst);
    if (NULL == BtSettingPairedDeviceInfoModelInst) {
        return;
    }

    if (NULL != BtSettingPairedDeviceInfoModelInst) {
        //  if AVP is connected         <- UT1
        if (BtSetting_ProfileId_AVP & (BtSettingPairedDeviceInfoModelInst->getConnectedFunction())) {
            // request FC to disconnect
            if (NULL != BtSettingFcProxyInst) {
                QMap<QString, QVariant> qmap;
                qmap.insert(FC_BT_SETTING_PAR_KEY_ADDRESS, m_addr);
                qint16 m_profile = BtSetting_DeviceType_AudioPlayer;
                qmap.insert(FC_BT_SETTING_PAR_KEY_DEVICE_TYPE, m_profile);
                emit request(FC_BT_SETTING_REQ_DISCONNECT_DEVICE_TYPE, QVariant(qmap));
                NGLogDebug(LogTag_BT_Setup, "[%s] Request FC disconnectAsAudio device: %llu", __PRETTY_FUNCTION__, m_addr);
            }
        }
        // else if AVP is not connected
        else {

            m_profFlag = BtSetupCommon::DevType_Audio;

            bool isEU = PhoneCommon::GetInstance()->getUICFunc()->kindPNR().isRegion_EU();
            bool isChina = PhoneCommon::GetInstance()->getUICFunc()->kindPNR().isRegion_CHINA();

            NGLogDebug(LogTag_BT_Setup,  "[%s] isEU is: %d", __PRETTY_FUNCTION__, isEU);
            NGLogDebug(LogTag_BT_Setup,  "[%s] isChina is: %d", __PRETTY_FUNCTION__, isChina);

            // if is EU and China
            if (isEU || isChina) {
                // if data is communicating         <- UT2
                if (BtSettingPropertyModelInst->isDataCommunication()) {
                    // open ONS to stop data communicating
                    this->openONSWithIdAndContext(MSG_07_09_03_00);
                }
                // else if data is not communicating
                else {
                    // if other device has connected AVP            <-UT3
                    if (BtSettingPropertyModelInst->getAvpConnectedStatus()) {
                        // open MSG_07_09_03_03
                        this->openONSWithIdAndContext(MSG_07_09_03_03);
                    }
                    // else if other device has not connected AVP           <- UT4
                    else {
                        // ScreenTransfer STP_profConnecting (connect as audio player)
                        this->transferToConnecting(BtSetupCommon::DevType_Audio);
                    }
                }
            }
            // else if is other region
            else {
                // if other device has connected AVP            <- UT5
                if (BtSettingPropertyModelInst->getAvpConnectedStatus()) {
                    // open MSG_07_09_03_03
                    this->openONSWithIdAndContext(MSG_07_09_03_03);
                }
                // else if other device has not connected AVP           <- UT6
                else {
                    // ScreenTransfer STP_profConnecting (connect as audio player)
                    this->transferToConnecting(BtSetupCommon::DevType_Audio);
                }
            }
        }
    }
}



// click SetSubPhone button
/*
 * unitTest's usecase
 * UT: whether the function execution is completed
*/
void STP_ConnStatus::onSubPhoneBtnClicked()
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<XX-XX-XX-XX # 0.000>
    */

    NGLogDebug(LogTag_BT_Setup, "[%s] BtSetupCommonInst is: %p", __PRETTY_FUNCTION__, BtSetupCommonInst);
    if (NULL != BtSetupCommonInst) {
        BtSetupCommonInst->setSelectDeviceBtAddr(m_addr);
    }

    // ScreenTransfer(STP_SubPhoneSetting)
    NGLogDebug(LogTag_BT_Setup, "[%s] MIST to [GoSubPhoneSetting]", __PRETTY_FUNCTION__);
    APP::MIST(PhoneCommonInst->getAppId())->trigger(TRIGGER_GOSUBPHONESETTING);
}

// click DevInfo button
/*
 * unitTest's usecase
 * UT: whether the function execution is completed
*/
void STP_ConnStatus::onDevInfoBtnClicked()
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<XX-XX-XX-XX # 0.000>
    */

    // ScreenTransfer(STP_DevInfo)
    NGLogDebug(LogTag_BT_Setup, "[%s] MIST to [GoDevInfo]", __PRETTY_FUNCTION__);
    APP::MIST(PhoneCommonInst->getAppId())->trigger(TRIGGER_GODEVINFO);
}

// click Back button
/*
 * unitTest's usecase
 * UT: whether the function execution is completed
*/
void STP_ConnStatus::onBackBtnClicked()
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<XX-XX-XX-XX # 0.000>
    */

    // set share data
    APP::SetShareDataStr(UI_ShareData_Key_TransFrom, UI_ShareData_Value_Str_Invalid);

    // ScreenTransfer(STP_ConnStatus)
    NGLogDebug(LogTag_BT_Setup, "[%s] MIST to [GOTOPBACK]", __PRETTY_FUNCTION__);
    APP::MIST(PhoneCommonInst->getAppId())->trigger(TRIGGER_GOTOPBACK);
}

// close ONS
/*
 * unitTest's usecase
 * UT: whether the function execution is completed
*/
void STP_ConnStatus::onONSClosed(int ONSId)
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<XX-XX-XX-XX # 0.000>
    */

    NGLogDebug(LogTag_BT_Setup, "[%s] called", __PRETTY_FUNCTION__);

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
 * UT1: if ONSId is MSG_07_09_03_00, btnId is Yes
 * UT2: if ONSId is MSG_07_09_03_00, btnId is No or back
 * UT3: if ONSId is MSG_07_09_03_00, btnId is error
 * UT4: if ONSId is MSG_07_09_03_01, btnId is Yes
 * UT5: if ONSId is MSG_07_09_03_01, btnId is No or back
 * UT6: if ONSId is MSG_07_09_03_01, btnId is error
 * UT7: if ONSId is MSG_07_09_03_02, btnId is Yes
 * UT8: if ONSId is MSG_07_09_03_02, btnId is No or back
 * UT9: if ONSId is MSG_07_09_03_02, btnId is error
 * UT10: if ONSId is MSG_07_09_03_03, btnId is Yes
 * UT11: if ONSId is MSG_07_09_03_03, btnId is No or back
 * UT12: if ONSId is MSG_07_09_03_03, btnId is error
 * UT13: if ONSId is error
*/
void STP_ConnStatus::onONSClicked(int ONSId, int btnId)
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<XX-XX-XX-XX # 0.000>
    */

    NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingPairedDeviceInfoModelInst is: %p", __PRETTY_FUNCTION__, BtSettingPairedDeviceInfoModelInst);
    if (NULL == BtSettingPairedDeviceInfoModelInst) {
        return;
    }

    NGLogDebug(LogTag_BT_Setup, "onONSClicked:: [ %d ]", ONSId);
    NGLogDebug(LogTag_BT_Setup, "onONSClicked:: [ %d ]", btnId);
    // ONS to stop data communicating or not
    if (MSG_07_09_03_00 == ONSId) {
        // if btnId is Yes          <- UT1
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
        // else if btnId is No or back          < -UT2
        else if ((NGONSBtnId_Second == btnId) || (NGONSBtnId_Back == btnId)) {
            NGLogDebug(LogTag_BT_Setup, "[%s] btnId: [%d]", __PRETTY_FUNCTION__, btnId);
        }
        // else if btnId is error           <- UT3
        else {
            NGLogDebug(LogTag_BT_Setup, "[%s] btnId error", __PRETTY_FUNCTION__);
        }
        // GetNGONSAPI()->unregisterONSCallBack(*this);
    }
    // ONS to disconnect other HFP or not
    else if (MSG_07_09_03_02 == ONSId) {
        // if btnId is Yes           <- UT4
        if (NGONSBtnId_First == btnId) {
            if (NULL != BtSettingFcProxyInst) {
                // to disconnect other HFP
                QMap<QString, QVariant> qmap;
                qint16 m_profile = BtSetting_DeviceType_MainPhone;
                qmap.insert(FC_BT_SETTING_PAR_KEY_ADDRESS, m_otherAddr);
                qmap.insert(FC_BT_SETTING_PAR_KEY_DEVICE_TYPE, m_profile);
                emit request(FC_BT_SETTING_REQ_DISCONNECT_DEVICE_TYPE, QVariant(qmap));
                NGLogDebug(LogTag_BT_Setup, "[%s] Request FC disconnect all other HFP", __PRETTY_FUNCTION__);
            }
        }
        // else if btnId is No or back           <- UT5
        else if ((NGONSBtnId_Second == btnId) || (NGONSBtnId_Back == btnId)) {
            NGLogDebug(LogTag_BT_Setup, "[%s] btnId: [%d]", __PRETTY_FUNCTION__, btnId);
        }
        // else if btnId is error           <- UT6
        else {
            NGLogDebug(LogTag_BT_Setup, "[%s] btnId error", __PRETTY_FUNCTION__);
        }
    }
    // ONS to disconnect other AVP or not
    else if (MSG_07_09_03_03 == ONSId) {
        // if btnId is Yes           <- UT7
        if (NGONSBtnId_First == btnId) {
            if (NULL != BtSettingFcProxyInst) {
                // to disconnect other AVP
                QMap<QString, QVariant> qmap;
                qint16 m_profile = BtSetting_DeviceType_AudioPlayer;
                qmap.insert(FC_BT_SETTING_PAR_KEY_ADDRESS, m_otherAddr);
                qmap.insert(FC_BT_SETTING_PAR_KEY_DEVICE_TYPE, m_profile);
                emit request(FC_BT_SETTING_REQ_DISCONNECT_DEVICE_TYPE, QVariant(qmap));
                NGLogDebug(LogTag_BT_Setup, "[%s] Request FC disconnect all other AVP", __PRETTY_FUNCTION__);
            }
        }
        // else if btnId is No or back           <- UT8
        else if ((NGONSBtnId_Second == btnId) || (NGONSBtnId_Back == btnId)) {
            NGLogDebug(LogTag_BT_Setup, "[%s] btnId: [%d]", __PRETTY_FUNCTION__, btnId);
        }
        // else if btnId is error           <- UT9
        else {
            NGLogDebug(LogTag_BT_Setup, "[%s] btnId error", __PRETTY_FUNCTION__);
        }
        // GetNGONSAPI()->unregisterONSCallBack(*this);
    }
    // ONS to disconnect other HFP and AVP or not
    else if (MSG_07_09_03_04 == ONSId) {
        // if btnId is Yes           <- UT10
        if (NGONSBtnId_First == btnId) {
            // if this device support HFP
            if (!(BtSettingPairedDeviceInfoModelInst->isSupportHFP())) {
                NGLogDebug(LogTag_BT_Setup,  "[%s] this device does not support HFP", __PRETTY_FUNCTION__);
                m_profFlag = BtSetupCommon::DevType_Audio;
            }
            if (NULL != BtSettingFcProxyInst) {
                // to disconnect other HFP and AVP
                QMap<QString, QVariant> qmap;
                emit request(FC_BT_SETTING_REQ_DISCONNECT_ALL_OF_THE_DEVICES, QVariant(qmap));
                NGLogDebug(LogTag_BT_Setup, "[%s] Request FC disconnect all other HFP and AVP", __PRETTY_FUNCTION__);
            }
        }
        // else if btnId is NO or back           <- UT11
        else if ((NGONSBtnId_Second == btnId) || (NGONSBtnId_Back == btnId)) {
            NGLogDebug(LogTag_BT_Setup, "[%s] btnId: [%d]", __PRETTY_FUNCTION__, btnId);
        }
        // else if btnId is error           <- UT12
        else {
            NGLogDebug(LogTag_BT_Setup, "[%s] btnId error", __PRETTY_FUNCTION__);
        }
    }
    // else if ONSId is error           <- UT13
    else {
        NGLogDebug(LogTag_BT_Setup, "[%s] ONSId error", __PRETTY_FUNCTION__);
    }
}

// notify from FC
/*
 * unitTest's usecase
 * UT1: uri is disconnect device complete, disconnect other device, type is mainPhone
 * UT2: uri is disconnect device complete, disconnect other device, type is audioPlayer
 * UT3: uri is disconnect device complete, disconnect other device, type is error
 * UT4: uri is disconnect device complete, disconnect this device, type is mainPhone
 * UT5: uri is disconnect device complete, disconnect this device, type is audioPlayer
 * UT6: uri is disconnect device complete, disconnect this device, type is error
 * UT7: uri is disconnect device complete, addr is error
 * UT8: uri is BT error mode automatic return processing
 * UT9: uri is data communicating ending
 * UT10: uri is disconnect all other device finish, type is all
 * UT11: uri is disconnect all other device finish, type is audioPlayer
 * UT12: uri is set devInfoModel finish
 * UT13: uri is error
*/
void STP_ConnStatus::onNotify(QString uri, QVariant data)
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<seq_DisconnectDevice # 1.01>
    */

    NGLogDebug(LogTag_BT_Setup, "[%s] receive notify from FC: %s", __PRETTY_FUNCTION__, uri.toStdString().c_str());
    NGLogDebug(LogTag_BT_Setup,  "[%s] m_proFlag is: %d", __PRETTY_FUNCTION__, m_profFlag);

    // disconnect device complete
    if (FC_BT_SETTING_NOTIFY_DISCONNECT_DEVICE_TYPE_FINISH == uri) {
        QMap<QString, QVariant> qMap = data.toMap();
        // get BtAddr from (data -> QMap)
        if (!qMap.contains(FC_BT_SETTING_PAR_KEY_ADDRESS)) {
            NGLogDebug(LogTag_BT_Setup,  "[%s] addr is null", __PRETTY_FUNCTION__);
            return;
        }
        QMap<QString, QVariant>::iterator numAddr = qMap.find(FC_BT_SETTING_PAR_KEY_ADDRESS);
        quint64 addr = numAddr.value().toUInt();
        NGLogDebug(LogTag_BT_Setup,  "[%s] addr is: %d", __PRETTY_FUNCTION__, addr);
        // disconnect other device
        if (m_otherAddr == addr) {
            // get device profile
            if (!qMap.contains(FC_BT_SETTING_PAR_KEY_DEVICE_TYPE)) {
                NGLogDebug(LogTag_BT_Setup,  "[%s] devType is null", __PRETTY_FUNCTION__);
                return;
            }
            QMap<QString, QVariant>::iterator numProf = qMap.find(FC_BT_SETTING_PAR_KEY_DEVICE_TYPE);
            quint64 profile = numProf.value().toInt();
            NGLogDebug(LogTag_BT_Setup,  "[%s] profile is: %d", __PRETTY_FUNCTION__, profile);
            // if disconnect mainPhone          <- UT1
            if (BtSetting_DeviceType_MainPhone == profile) {
                NGLogDebug(LogTag_BT_Setup,  "[%s] receive notify disconnect other main Phone finish", __PRETTY_FUNCTION__);

                if (!(BtSetting_ProfileId_HFP & (BtSettingPairedDeviceInfoModelInst->getConnectedFunction())) && (BtSettingPropertyModelInst->getHfpConnectedStatus())) {
                    return;
                }

                // hfpBtnClick second time
                this->onHfpBtnClicked();
            }
            // if disconnect AVP            <- UT2
            else if (BtSetting_DeviceType_AudioPlayer == profile) {
                NGLogDebug(LogTag_BT_Setup,  "[%s] receive notify disconnect other Audio finish", __PRETTY_FUNCTION__);

                if (!(BtSetting_ProfileId_AVP & (BtSettingPairedDeviceInfoModelInst->getConnectedFunction())) && (BtSettingPropertyModelInst->getAvpConnectedStatus())) {
                    return;
                }

                // avpBtnClick seond time
                this->onAvpBtnClicked();
            }
            // else if type is error            <- UT3
            else {
                NGLogDebug(LogTag_BT_Setup,  "[%s] receive notify of disconnect other device error", __PRETTY_FUNCTION__);
            }
        }
        // else if disconnect this device
        else if (m_addr == addr) {
            if (!qMap.contains(FC_BT_SETTING_PAR_KEY_DEVICE_TYPE)) {
                NGLogDebug(LogTag_BT_Setup,  "[%s] devType is null", __PRETTY_FUNCTION__);
                return;
            }
            QMap<QString, QVariant>::iterator numProf = qMap.find(FC_BT_SETTING_PAR_KEY_DEVICE_TYPE);
            quint64 profile = numProf.value().toInt();
            NGLogDebug(LogTag_BT_Setup,  "[%s] devtype is: %d", __PRETTY_FUNCTION__, profile);
            // if disconnect mainPhone          <- UT4
            if (BtSetting_DeviceType_MainPhone == profile) {
                NGLogDebug(LogTag_BT_Setup,  "[%s] receive notify disconnect this main Phone finish", __PRETTY_FUNCTION__);
            }
            // else if disconnect AVP            <- UT5
            else if (BtSetting_DeviceType_AudioPlayer == profile) {
                NGLogDebug(LogTag_BT_Setup,  "[%s] receive notify disconnect this Audio finish", __PRETTY_FUNCTION__);
            }
            // else if type is error            <- UT6
            else {
                NGLogDebug(LogTag_BT_Setup,  "[%s] receive notify of disconnect this device type error", __PRETTY_FUNCTION__);
            }
        }
        // else if addr is error            <- UT7
        else {
            NGLogDebug(LogTag_BT_Setup,  "[%s] receive notify of disconnect this device addr error", __PRETTY_FUNCTION__);
        }
    }
    // else if BT error mode automatic return processing            <- UT8
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
    // else if data communicating ending            <- UT9
    else if (FC_BT_SETTING_NOTIFY_DISCONNECT_DATA_COMMUNICATION_FINISH == uri) {
        NGLogDebug(LogTag_BT_Setup,  "[%s] receive notify of stop data communicating finish", __PRETTY_FUNCTION__);

//        // if MSG_07_09_03_01 is open
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

    // else if disconnect all other device finish
    else if (FC_BT_SETTING_NOTIFY_DISCONNECT_ALL_OF_THE_DEVICES_FINISH == uri) {
        NGLogDebug(LogTag_BT_Setup,  "[%s] receive notify of disconnect all other devices", __PRETTY_FUNCTION__);

        // m_profFlag = BtSetupCommon::DevType_All;

        NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingPairedDeviceInfoModelInst is: %p", __PRETTY_FUNCTION__, BtSettingPairedDeviceInfoModelInst);
        if (NULL == BtSettingPairedDeviceInfoModelInst) {
            return;
        }

        // if any other device has connect HFP or AVP
        if ((!(BtSetting_ProfileId_HFP & (BtSettingPairedDeviceInfoModelInst->getConnectedFunction())) && (BtSettingPropertyModelInst->getHfpConnectedStatus())) || (!(BtSetting_ProfileId_AVP & (BtSettingPairedDeviceInfoModelInst->getConnectedFunction())) && (BtSettingPropertyModelInst->getAvpConnectedStatus()))) {
            return;
        }
        // if connect all           <- UT10
        if (BtSetupCommon::DevType_All == m_profFlag) {
            // ScreenTransfer STP_profConnecting (connect all)
            this->transferToConnecting(BtSetupCommon::DevType_All);
        }
        // else if connect Audio        <- UT11
        else if (BtSetupCommon::DevType_Audio == m_profFlag) {
            // ScreenTransfer STP_profConnecting (connect audio)
            this->transferToConnecting(BtSetupCommon::DevType_Audio);
        }
    }

    // else if set devInfoModel finish          <- UT12
    else if (FC_BT_SETTING_NOTIFY_SET_DEVICE_DEFAULT_FINISH == uri) {
        // set new device name
        NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingPairedDeviceInfoModelInst is: %p", __PRETTY_FUNCTION__, BtSettingPairedDeviceInfoModelInst);
        if (NULL != BtSettingPairedDeviceInfoModelInst) {
            m_devName = BtSettingPairedDeviceInfoModelInst->getName();
            NGLogDebug(LogTag_BT_Setup, "[%s] m_devName is: %s", __PRETTY_FUNCTION__, m_devName.toStdString().c_str());

            // save addr in APP
            APP::SetAppContext(PhoneCommonInst->getAppId(), UI_AppContext_Key_STP_ConnStatus_DeviceName, m_devName.toStdString());
        }

        // Initialize connect and disconnect button text
        if (NULL != m_connectBtn) {

            QString StrConnect = QString().sprintf(NQResourceManagerInst.getString("STR_MM_07_09_03_RES_00").toStdString().c_str(), m_devName.toStdString().c_str());

            m_connectBtn->setText(StrConnect);
            NGLogDebug(LogTag_BT_Setup, "[%s] initialize connect btn text", __PRETTY_FUNCTION__);
        }
        if (NULL != m_disconnectBtn) {

            QString StrDisconnect = QString().sprintf(NQResourceManagerInst.getString("STR_MM_07_09_03_RES_01").toStdString().c_str(), m_devName.toStdString().c_str());

            m_disconnectBtn->setText(StrDisconnect);
            NGLogDebug(LogTag_BT_Setup, "[%s] initialize disconnect btn text", __PRETTY_FUNCTION__);
        }
    }
    // else if uri is error         <- UT13
    else {
        NGLogDebug(LogTag_BT_Setup,  "[%s] receive notify erro", __PRETTY_FUNCTION__);
    }

    this->showLog();
}


// hansfree notify of call status
/*
 * unitTest's usecase
 * UT: whether the function execution is completed
*/
void STP_ConnStatus::onHandsfreeNotify()
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
    m_callStatus = BtHandsfreePropertyModelInst->getCallStatus();
    NGLogDebug(LogTag_BT_Setup, "[%s] callStatus is: %d", __PRETTY_FUNCTION__, m_callStatus);

    // init OnsStstus
    initOnsStatus();
}

// set ONS button status with error mode
/*
 * unitTest's usecase
 * UT1: if in bt error mode
 * UT2: if device is connected, call status is idle
 * UT3: if device is connected, call status is not idle
 * UT4: if device is disconencted
*/
void STP_ConnStatus::setOnsButtonStatusWithErrorMode(int onsId)
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
        // if in Bt error mode          <- UT1
        if (m_error) {
            onsContext.buttonStateList.push_back(NGButtonState_Inactive);
        }
        // else if HFP main or sub has connected
        else if ((BtSettingPropertyModelInst->getHfpConnectedStatus()) || (BtSettingPropertyModelInst->getSubHfpConnectedStatus())) {
            // if is not talking,sending,receiving          <- UT2
            if (BtHandsfreeEnum::CallStatus_Idle == m_callStatus) {
                onsContext.buttonStateList.push_back(NGButtonState_Active);
            }
            // else if is talking,sending,receiving         <- UT3
            else {
                onsContext.buttonStateList.push_back(NGButtonState_Inactive);
            }
        }
        // else if HFP main or sub has not connected            <- UT4
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
        if (NULL != GetNGONSAPI()) {
            if (NGONSStatus_Closed != GetNGONSAPI()->getONSStatus(onsId)) {
               GetNGONSAPI()->updateONS(onsId, onsContext);
            }
            NGLogDebug(LogTag_BT_Setup, "[%s] ONS: %d is %d", __PRETTY_FUNCTION__, onsId, GetNGONSAPI()->getONSStatus(onsId));
        }
        else {
            NGLogDebug(LogTag_BT_Setup, "[%s] GetNGONSAPI() is NULL, can not set button status to ONS", __PRETTY_FUNCTION__);
        }

    }
}

// set ONS button status without error mode
/*
 * unitTest's usecase
 * UT1: if device is connected, call status is idle
 * UT2: if device is connected, call status is not idle
 * UT3: if device is disconencted
*/
void STP_ConnStatus::setOnsButtonStatusWithoutErrorMode(int onsId)
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
            // if is not talking,sending,receiving          <- UT1
            if (BtHandsfreeEnum::CallStatus_Idle == m_callStatus) {
                onsContext.buttonStateList.push_back(NGButtonState_Active);
                onsContext.buttonStateList.push_back(NGButtonState_Active);
            }
            // else if is talking,sending,receiving         <- UT2
            else {
                onsContext.buttonStateList.push_back(NGButtonState_Inactive);
                onsContext.buttonStateList.push_back(NGButtonState_Inactive);
            }
        }
        // else if HFP main or sub has not connected        <- UT3
        else {
            onsContext.buttonStateList.push_back(NGButtonState_Active);
            onsContext.buttonStateList.push_back(NGButtonState_Active);
        }

        // set button status to ONS
        if (NULL != GetNGONSAPI()) {
            if (NGONSStatus_Closed != GetNGONSAPI()->getONSStatus(onsId)) {
               GetNGONSAPI()->updateONS(onsId, onsContext);
            }
            NGLogDebug(LogTag_BT_Setup, "[%s] ONS: %d is %d", __PRETTY_FUNCTION__, onsId, GetNGONSAPI()->getONSStatus(onsId));
        }
        else {
            NGLogDebug(LogTag_BT_Setup, "[%s] GetNGONSAPI() is NULL, can not set button status to ONS", __PRETTY_FUNCTION__);
        }

    }
}

// init OnsStstus
// hansfree notify of call status
/*
 * unitTest's usecase
 * UT: whether the function execution is completed
*/
void STP_ConnStatus::initOnsStatus()
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<XX-XX-XX-XX # 0.000>
    */

    this->showLog();

    NGLogDebug(LogTag_BT_Setup, "[%s] called", __PRETTY_FUNCTION__);
    this->setOnsButtonStatusWithErrorMode(MSG_07_09_03_02);
    this->setOnsButtonStatusWithErrorMode(MSG_07_09_03_03);
    this->setOnsButtonStatusWithErrorMode(MSG_07_09_03_04);
    this->setOnsButtonStatusWithoutErrorMode(MSG_07_09_03_00);
}


// show log
// hansfree notify of call status
/*
 * unitTest's usecase
 * UT: whether the function execution is completed
*/
void STP_ConnStatus::showLog()
{
    NGLogDebug(LogTag_BT_Setup,  "[%s] BtHandsfreePropertyModelInst is %p", __PRETTY_FUNCTION__, BtHandsfreePropertyModelInst);
    if (NULL != BtHandsfreePropertyModelInst) {
        NGLogDebug(LogTag_BT_Setup,  "[%s] callStatus is %d", __PRETTY_FUNCTION__, BtHandsfreePropertyModelInst->getCallStatus());
    }

    NGLogDebug(LogTag_BT_Setup,  "[%s] BtSettingPropertyModelInst is %p", __PRETTY_FUNCTION__, BtSettingPropertyModelInst);
    if (NULL != BtSettingPropertyModelInst) {
        NGLogDebug(LogTag_BT_Setup,  "[%s] systeminfo mainHfp is %d", __PRETTY_FUNCTION__, BtSettingPropertyModelInst->getHfpConnectedStatus());
        NGLogDebug(LogTag_BT_Setup,  "[%s] systeminfo subHfp is %d", __PRETTY_FUNCTION__, BtSettingPropertyModelInst->getSubHfpConnectedStatus());
        NGLogDebug(LogTag_BT_Setup,  "[%s] systeminfo Avp is %d", __PRETTY_FUNCTION__, BtSettingPropertyModelInst->getAvpConnectedStatus());
    }

    NGLogDebug(LogTag_BT_Setup,  "[%s] BtSettingPropertyModelInst is %p", __PRETTY_FUNCTION__, BtSettingPropertyModelInst);
    if (NULL != BtSettingPropertyModelInst) {
        NGLogDebug(LogTag_BT_Setup,  "[%s] FC isError is %d", __PRETTY_FUNCTION__, BtSettingPropertyModelInst->isErrormode());
        NGLogDebug(LogTag_BT_Setup,  "[%s] my isError is %d", __PRETTY_FUNCTION__, m_error);

        NGLogDebug(LogTag_BT_Setup,  "[%s] HFPAvailable is: %d", __PRETTY_FUNCTION__, BtSettingPropertyModelInst->isHFPAvailable());
    }

    NGLogDebug(LogTag_BT_Setup,  "[%s] BtSettingMainDeviceInfoModelInst is: %p", __PRETTY_FUNCTION__, BtSettingMainDeviceInfoModelInst);
    if (NULL != BtSettingMainDeviceInfoModelInst) {
        NGLogDebug(LogTag_BT_Setup,  "[%s] mainPhone addr is %llu", __PRETTY_FUNCTION__, BtSettingMainDeviceInfoModelInst->getBdAddr());
        NGLogDebug(LogTag_BT_Setup,  "[%s] mainPhone name is: %s", __PRETTY_FUNCTION__, BtSettingMainDeviceInfoModelInst->getName().toStdString().c_str());
    }

    NGLogDebug(LogTag_BT_Setup,  "[%s] BtSettingPairedDeviceInfoModelInst is: %p", __PRETTY_FUNCTION__, BtSettingPairedDeviceInfoModelInst);
    if (NULL != BtSettingPairedDeviceInfoModelInst) {
        NGLogDebug(LogTag_BT_Setup,  "[%s] device connected Function is: %d", __PRETTY_FUNCTION__, BtSettingPairedDeviceInfoModelInst->getConnectedFunction());
        if (BtSetting_ProfileId_HFP & (BtSettingPairedDeviceInfoModelInst->getConnectedFunction())) {
            NGLogDebug(LogTag_BT_Setup,  "[%s] device has connected HFP", __PRETTY_FUNCTION__);
        }
        else {
            NGLogDebug(LogTag_BT_Setup,  "[%s] device has not connected HFP", __PRETTY_FUNCTION__);
        }

        if (BtSetting_ProfileId_AVP & (BtSettingPairedDeviceInfoModelInst->getConnectedFunction())) {
            NGLogDebug(LogTag_BT_Setup,  "[%s] device has connected AVP", __PRETTY_FUNCTION__);
        }
        else {
            NGLogDebug(LogTag_BT_Setup,  "[%s] device has not connected AVP", __PRETTY_FUNCTION__);
        }

        NGLogDebug(LogTag_BT_Setup,  "[%s] isSupportSPP is: %d", __PRETTY_FUNCTION__, BtSettingPairedDeviceInfoModelInst->isSupportSPP());
        NGLogDebug(LogTag_BT_Setup,  "[%s] isSPPConnected is: %d", __PRETTY_FUNCTION__, BtSettingPairedDeviceInfoModelInst->isSPPConnected());
        NGLogDebug(LogTag_BT_Setup,  "[%s] isTSLSupported is: %d", __PRETTY_FUNCTION__, BtSettingPairedDeviceInfoModelInst->isTSLSupported());
        NGLogDebug(LogTag_BT_Setup,  "[%s] isTSLConnected is: %d", __PRETTY_FUNCTION__, BtSettingPairedDeviceInfoModelInst->isTSLConnected());
    }
}

// second connectting after disconnect data communicating finish
/*
 * unitTest's usecase
 * UT1: flag is connect all, any other device has connected HFP or AVP
 * UT2: flag is connect all, any other device has not connected HFP or AVP, this device support HFP
 * UT3: flag is connect all, any other device has not connected HFP or AVP, this device does not support HFP
 * UT4: flag is connect main phone, main Phone has connected
 * UT5: flag is connect main phone, main Phone has not connected
 * UT6: flag is connect Audio Player, AVP has connected
 * UT7: flag is connect Audio Player, AVP has not connected
 * UT8: flag is error
*/
void STP_ConnStatus::secondConnect()
{
    /*
    * ReferenceSequence:<SequenceName # Version>
    * @datalist:<XX-XX-XX-XX # 0.000>
    */

    NGLogDebug(LogTag_BT_Setup, "[%s] called", __PRETTY_FUNCTION__);

    NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingPropertyModelInst is: %p", __PRETTY_FUNCTION__, BtSettingPropertyModelInst);
    if (NULL == BtSettingPropertyModelInst) {
        return;
    }

    if (BtSettingPropertyModelInst->isDataCommunication()) {
        NGLogDebug(LogTag_BT_Setup, "[%s] stop communicating failed", __PRETTY_FUNCTION__);
        return;
    }

    // if connect all
    if (BtSetupCommon::DevType_All == m_profFlag) {
        // HFP status
        bool anyHfpConnected = false;
        if (BtSettingPropertyModelInst->getHfpConnectedStatus()) {
            anyHfpConnected = true;
        }

        bool thisDeviceConnectedHfp = BtSettingPairedDeviceInfoModelInst->isHFPConnected();

        // AVP status
        bool anyAvpConnected = false;
        if (BtSettingPropertyModelInst->getAvpConnectedStatus()) {
            anyAvpConnected = true;
        }

        bool thisDeviceConnectedAvp = BtSettingPairedDeviceInfoModelInst->isAVPConnected();

        // if any other device has connected HFP or AVP         <- UT1
        if (((!thisDeviceConnectedHfp) && anyHfpConnected) || ((!thisDeviceConnectedAvp) && anyAvpConnected)) {
            NGLogDebug(LogTag_BT_Setup,  "[%s] other device has connected HFP or AVP", __PRETTY_FUNCTION__);
            // open MSG_07_09_03_04
            this->openONSWithIdAndContext(MSG_07_09_03_04);
        }
        // else if other device has not connected HFP or AVP
        else {
            // if this device support HFP           <- UT2
            if (BtSettingPairedDeviceInfoModelInst->isSupportHFP()) {
                NGLogDebug(LogTag_BT_Setup,  "[%s] any other Device has not connected, this device support HFP", __PRETTY_FUNCTION__);
                // ScreenTransfer STP_profConnecting (connect all)
                NGLogDebug(LogTag_BT_Setup, "[%s] readly to transfer to Connect ALL", __PRETTY_FUNCTION__);
                this->transferToConnecting(BtSetupCommon::DevType_All);
            }
            // else if this device does not support HFP         <- UT3
            else {
                NGLogDebug(LogTag_BT_Setup,  "[%s] any other Device has not connected, this device does not support HFP", __PRETTY_FUNCTION__);
                // ScreenTransfer STP_profConnecting (connect Audio)
                NGLogDebug(LogTag_BT_Setup, "[%s] readly to transfer to Connect Audio", __PRETTY_FUNCTION__);
                this->transferToConnecting(BtSetupCommon::DevType_Audio);
            }
        }
    }
    // else if connect main phone
    else if (BtSetupCommon::DevType_MainPhone == m_profFlag) {
        // if main Phone has connected          <-UT4
        if (BtSettingPropertyModelInst->getHfpConnectedStatus()) {
            // open MSG_07_09_03_02
            this->openONSWithIdAndContext(MSG_07_09_03_02);
        }
        // else if main Phone has not connected         <- UT5
        else {
            NGLogDebug(LogTag_BT_Setup, "[%s] readly to ScreenTransfer connect mainPhone", __PRETTY_FUNCTION__);
            // ScreenTransfer STP_profConnecting (connect as main phone)
            this->transferToConnecting(BtSetupCommon::DevType_MainPhone);
        }
    }
    // else if connect Audio Player
    else if (BtSetupCommon::DevType_Audio == m_profFlag) {
        // if AVP has connected             <- UT6
        if (BtSettingPropertyModelInst->getAvpConnectedStatus()) {
            // open MSG_07_09_03_03
            this->openONSWithIdAndContext(MSG_07_09_03_03);
        }
        // else if AVP has not connected             <- UT7
        else {
            NGLogDebug(LogTag_BT_Setup, "[%s] readly to ScreenTransfer connect Audio", __PRETTY_FUNCTION__);
            // ScreenTransfer STP_profConnecting (connect as audio player)
            this->transferToConnecting(BtSetupCommon::DevType_Audio);
        }
    }
    // else if connect unknow type          <- UT8
    else {
        NGLogDebug(LogTag_BT_Setup, "[%s] m_profFlag is error", __PRETTY_FUNCTION__);
    }
}

/// systemLanguageChanged
void STP_ConnStatus::systemLanguageChanged()
{
    NGLogDebug(LogTag_BT_Setup, "STP_ConnStatus::systemLanguageChanged() start");
    m_devName = QString(APP::GetAppContext(PhoneCommonInst->getAppId(), UI_AppContext_Key_STP_ConnStatus_DeviceName).c_str());

    if (NULL != BtSetupCommonInst) {
        BtSetupCommonInst->notifyTitleChanged(m_devName, BtSetupCommon::ContectType_RawString);
    }

    NGLogDebug(LogTag_BT_Setup, "[%s] m_devName is: %s", __PRETTY_FUNCTION__, m_devName.toStdString().c_str());

    if (NULL != m_connectBtn) {
        QString StrConnect = QString().sprintf(NQResourceManagerInst.getString("STR_MM_07_09_03_RES_00").toStdString().c_str(), m_devName.toStdString().c_str());
        m_connectBtn->setText(StrConnect);
        NGLogDebug(LogTag_BT_Setup, "[%s] initialize connect btn text", __PRETTY_FUNCTION__);
    }
    if (NULL != m_disconnectBtn) {
        QString StrDisconnect = QString().sprintf(NQResourceManagerInst.getString("STR_MM_07_09_03_RES_01").toStdString().c_str(), m_devName.toStdString().c_str());
        m_disconnectBtn->setText(StrDisconnect);

        NGLogDebug(LogTag_BT_Setup, "[%s] initialize disconnect btn text", __PRETTY_FUNCTION__);
    }

    updateONSText();
}

/// updateONSText  when language changed
 void STP_ConnStatus::updateONSText()
 {
     NGLogDebug(LogTag_BT_Setup, "[%s] called ", __PRETTY_FUNCTION__);
       if (NGONSStatus_Closed != GetNGONSAPI()->getONSStatus(MSG_07_09_03_02)) {
           NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingPropertyModelInst is: %p", __PRETTY_FUNCTION__, BtSettingPropertyModelInst);
           if (NULL != BtSettingPropertyModelInst) {
               // get mainPhone name
               QString mainPhone = BtSettingPropertyModelInst->getMainPhoneName();
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

               onsContext.specId.specId1 = 6298113;
               onsContext.specId.specId2 = 6298114;
               onsContext.specId.specId3 = 6298115;

               // open ONS
               GetNGONSAPI()->updateONS(MSG_07_09_03_02, onsContext);

           }
       }

       if (NGONSStatus_Closed != GetNGONSAPI()->getONSStatus(MSG_07_09_03_03)) {
           NGLogDebug(LogTag_BT_Setup, "[%s] BtSettingPropertyModelInst is: %p", __PRETTY_FUNCTION__, BtSettingPropertyModelInst);
           if (NULL != BtSettingPropertyModelInst) {
               // get AudioPlayer name
               QString audioPlayer = BtSettingPropertyModelInst->getAudioPlayerName();
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

               onsContext.specId.specId1 = 6298241;
               onsContext.specId.specId2 = 6298242;
               onsContext.specId.specId3 = 6298243;

               // open ONS
               GetNGONSAPI()->updateONS(MSG_07_09_03_03, onsContext);
           }
       }

 }

/*---------------------------------------------------------------------------*/
// Private functions
/*---------------------------------------------------------------------------*/

/* EOF */
