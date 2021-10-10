//******************************************************************************
/*++
    FileName:        iMonitor.h
    Description:

--*/
//******************************************************************************
#ifndef __iMonitor_H__
#define __iMonitor_H__
//******************************************************************************
// clang-format off
//******************************************************************************
#define MONITOR_VERSION                       1010
#define MONITOR_MAX_BUFFER                    260
//******************************************************************************
#ifndef BIT
#define BIT(n) (1 << n)
#endif
//******************************************************************************
#ifndef FlagOn
#define FlagOn(n, x) ((n) & (x))
#endif
//******************************************************************************
enum emMSGType
{
    emMSGInternal                             = 0,
    emMSGProcess                              = 100,
    emMSGFile                                 = 200,
    emMSGRegistry                             = 300,
    emMSGSocket                               = 400,
    emMSGWFP                                  = 500,
    emMSGSystem                               = 600,
    emMSGMax                                  = 1000,
};
//******************************************************************************
enum emMSGTypeInternal
{
    emMSGInternalEnumProcess = emMSGInternal + 1,
    emMSGInternalEnumProtectRule,
    emMSGInternalEnd,
};
//******************************************************************************
enum emMSGTypeProcess
{
    emMSGProcessCreate = emMSGProcess + 1,
    emMSGProcessExit,
    emMSGProcessOpen,
    emMSGThreadCreate,
    emMSGThreadExit,
    emMSGThreadOpen,
    emMSGImageLoad,
    emMSGProcessStart,
    emMSGThreadStart,
};
//******************************************************************************
enum emMSGTypeFile
{
    emMSGFileCreate = emMSGFile + 1,
    emMSGFilePostCreate,
    emMSGFileQueryOpen,
    emMSGFilePostQueryOpen,
    emMSGFileCleanup,
    emMSGFilePostCleanup_nosupport,
    emMSGFileCreateSection,
    emMSGFilePostCreateSection,
    emMSGFileRead,
    emMSGFilePostRead,
    emMSGFileWrite,
    emMSGFilePostWrite,
    emMSGFileCreateHardLink,
    emMSGFilePostCreateHardLink,
    emMSGFileRename,
    emMSGFilePostRename,
    emMSGFileDelete,
    emMSGFilePostDelete,
    emMSGFileSetSize,
    emMSGFilePostSetSize,
    emMSGFileSetBasicInfo,
    emMSGFilePostSetBasicInfo,
    emMSGFileFindFile,
    emMSGFilePostFindFile,
};
//******************************************************************************
enum emMSGTypeRegistry
{
    emMSGRegCreateKey = emMSGRegistry + 1,
    emMSGRegPostCreateKey,
    emMSGRegOpenKey,
    emMSGRegPostOpenKey,
    emMSGRegDeleteKey,
    emMSGRegPostDeleteKey,
    emMSGRegRenameKey,
    emMSGRegPostRenameKey,
    emMSGRegEnumKey,
    emMSGRegPostEnumKey,
    emMSGRegLoadKey,
    emMSGRegPostLoadKey,
    emMSGRegReplaceKey,
    emMSGRegPostReplaceKey,
    emMSGRegDeleteValue,
    emMSGRegPostDeleteValue,
    emMSGRegSetValue,
    emMSGRegPostSetValue,
};
//******************************************************************************
enum emMSGTypeSocket
{
    emMSGSocketCreate = emMSGSocket + 1,
    emMSGSocketPostCreate_nosupport,
    emMSGSocketControl,
    emMSGSocketPostControl,
    emMSGSocketConnect,
    emMSGSocketPostConnect,
    emMSGSocketSend,
    emMSGSocketPostSend_nosupport,
    emMSGSocketRecv,
    emMSGSocketPostRecv,
    emMSGSocketSendTo,
    emMSGSocketPostSendTo,
    emMSGSocketRecvFrom,
    emMSGSocketPostRecvFrom,
    emMSGSocketListen,
    emMSGSocketPostListen,
    emMSGSocketAccept,
    emMSGSocketPostAccept,
};
//******************************************************************************
enum emMSGTypeWFP
{
    emMSGWFPTcpConnect = emMSGWFP + 1,
    emMSGWFPUdpConnect,
    emMSGWFPTcpAccept,
    emMSGWFPUdpAccept,
};
//******************************************************************************
enum emMSGConfig
{
    emMSGConfigDefault                         = 0,
    emMSGConfigPost                            = BIT(0),
    emMSGConfigSend                            = BIT(1),
    emMSGConfigRule                            = BIT(2),
    emMSGConfigEnable                          = emMSGConfigPost | emMSGConfigSend | emMSGConfigRule,
    emMSGConfigIncludeKernelEvent              = BIT(10),
};
//******************************************************************************
enum emMSGAction
{
    emMSGActionDefault                         = 0,
    emMSGActionPass                            = 0,
    emMSGActionBlock                           = BIT(0),
    emMSGActionRedirect                        = BIT(1),
    emMSGActionGrantedAccess                   = BIT(2),
    emMSGActionTerminateProcess                = BIT(3),
    emMSGActionTerminateThread                 = BIT(4),
    emMSGActionLoadLibrary                     = BIT(5),
    emMSGActionRecord                          = BIT(20),
};
//******************************************************************************
enum emMSGDataType
{
    //
    //    ��������
    //
    emMSGDataUnknown                           = 0,
    emMSGDataULONG                             = 0x10000,
    emMSGDataULONGLONG                         = 0x20000,
    emMSGDataString                            = 0x30000,
    emMSGDataPath                              = 0x40000,
    emMSGDataBinary                            = 0x50000,
    emMSGDataCallstatck                        = 0x60000,

#define MSG_GET_BASE_TYPE(type)                (type & 0xFFFF0000)

    //
    //    ��չ����
    //
    emMSGDataBool = emMSGDataULONG + 1,
    emMSGDataHex,
    emMSGDataProcessAccess,
    emMSGDataThreadAccess,
    emMSGDataFileAccess,
    emMSGDataFileShareAccess,
    emMSGDataFileAttributes,
    emMSGDataFileDisposition,
    emMSGDataFileOptions,
    emMSGDataFilePageProtection,
    emMSGDataRegAccess,
    emMSGDataRegOptions,
    emMSGDataRegType,
    emMSGDataSocketIP,
    emMSGDataSocketPort,

    emMSGDataTime = emMSGDataULONGLONG + 1,
};
//******************************************************************************
enum emMSGField
{
    //
    //    �����ֶ�
    //
    emMSGFieldInvalid = -1,
    emMSGFieldCallstack = 0,
    emMSGFieldCurrentProcessCreateTime,
    emMSGFieldCurrentProcessName,
    emMSGFieldCurrentProcessPath,
    emMSGFieldCurrentProcessCommandline,
    emMSGFieldPrivateBegin,
    emMSGFieldPath = emMSGFieldPrivateBegin,

    //
    // �����ֶ�Ĭ������
    //
    emMSGFieldDefault = ~BIT(emMSGFieldCallstack),
    emMSGFieldInternal = -1 << emMSGFieldPrivateBegin,

    //
    // ��չ�ֶ�
    //
    emMSGFieldExtension = 32,
    emMSGFieldType,
    emMSGFieldSeqId,
    emMSGFieldStatus,
    emMSGFieldCurrentProcessId,
    emMSGFieldCurrentThreadId,
    emMSGFieldTime,
    emMSGFieldDetail,

    //
    // �û���չ�ֶ�
    //
    emMSGFieldCustomExtension = 1000,
};
//******************************************************************************
enum emMSGStatus
{
    emMSGStatusEnumBegin = 0x10000000,
    emMSGStatusEnumEnd,
};
//******************************************************************************
//
//    ������ --> Ӧ�ò㡿
//
//******************************************************************************
struct cxMSGHeader
{
    ULONG                Type;
    ULONG                Length;
    ULONG                Status;
    ULONG                Config;
    ULONG                SeqId;
    ULONG                Fields;
    ULONG                CurrentProcessId;
    ULONG                CurrentThreadId;
    ULONG                RuleId;
    ULONG                Reserved;
    ULONGLONG            Time;

    //
    //    ������Ŷ��cxMSGDataHeader + Data
    //
};
//******************************************************************************
struct cxMSGDataHeader 
{
    ULONG                Type;
    ULONG                Length;
    
    template<typename T>
    T*      GetData     (void)                { return (T*)(this + 1); }
    PVOID   GetData     (void)                { return (PVOID)(this + 1); }

    cxMSGDataHeader* Next(void)               { return (cxMSGDataHeader*)((ULONG_PTR)this + Length); }
};
//******************************************************************************
struct cxMSGAction
{
    ULONG                Action;
    union {
        ULONG            Params[3];
        ULONG            Access;
        struct {
            ULONG        ProcessId;
            ULONG        IP;
            ULONG        Port;
        };
    };
};
//******************************************************************************
//
//    ���û��� --> �����㡿
//
//******************************************************************************
struct cxMSGUserHeader 
{
    ULONG                Type;
};
//******************************************************************************
template<ULONG TYPE, typename T = void>
struct cxMSGUser : public cxMSGUserHeader, public T
{
    static constexpr auto TYPE = TYPE;

    cxMSGUser            (void)                { Type = TYPE; }
    T*                   GetData(void)         { return this; }
};
//******************************************************************************
template<ULONG TYPE>
struct cxMSGUser<TYPE, void> : public cxMSGUserHeader
{
    static constexpr auto TYPE = TYPE;

    cxMSGUser            (void)                { Type = TYPE; }
};
//******************************************************************************
enum emMSGUser
{
    emMSGUserBase                              = 0,
    emMSGUserControl                           = 100,
    emMSGUserRule                              = 200,

    emMSGUserConnect                           = emMSGUserBase + 1,
};
//******************************************************************************
struct cxMSGUserConnect : public cxMSGUser<emMSGUserConnect> 
{
    ULONG                Version               = MONITOR_VERSION;
};
//******************************************************************************
enum
{
    emUserSetGlobalConfig = emMSGUserControl + 1,
    emUserGetGlobalConfig,
    emUserSetMSGConfig,
    emUserGetMSGConfig,
    emUserEnableProtect,
    emUserDisableProtect,
    emUserAddProtectRule,
    emUserRemoveProtectRule,
    emUserRemoveAllProtectRule,
    emUserEnumProtectRule,
};
//******************************************************************************
struct cxUserGlobalConfig
{
    enum emSwitch {
        emSwitchIncludeVS                      = BIT(0),
        emSwitchIncludeSelf                    = BIT(1),
    };

    union {
        struct {
            ULONG        Switch;
            ULONG        LogLevel;
            ULONG        MaxCallstack;
            ULONG        MaxBinaryData;
            ULONG        MSGTimeoutMS;
        };

        ULONG            Data[32];
    };

    cxUserGlobalConfig()
    {
        memset(Data, 0, sizeof(Data));

        Switch = emSwitchIncludeVS;
        MaxCallstack = 64;
        MaxBinaryData = 4096;
        MSGTimeoutMS = 5000;
    }

    bool IsIncludeVS(void)
    {
        return FlagOn(Switch, emSwitchIncludeVS);
    }

    bool IsIncludeSelf(void)
    {
        return FlagOn(Switch, emSwitchIncludeSelf);
    }
};
//******************************************************************************
struct cxUserMSGConfig
{
    ULONG        Config[emMSGMax];
    ULONG        Fields[emMSGMax];

    cxUserMSGConfig()
    {
        for (int i = 0; i < emMSGMax; i++)
            Config[i] = (ULONG)emMSGConfigDefault;

        for (int i = 0; i < emMSGMax; i++)
            Fields[i] = (ULONG)emMSGFieldDefault;
    }
};
//******************************************************************************
enum emUserProtectType
{
    emProtectTypeTrustProcess = BIT(0),
    emProtectTypeProcessPath = BIT(1),
    emProtectTypeFilePath = BIT(2),
    emProtectTypeRegPath = BIT(3),
};
//******************************************************************************
struct cxUserProtectItem
{
    ULONG        ProtectType;
    WCHAR        Path[MONITOR_MAX_BUFFER];
};
//******************************************************************************
typedef cxMSGUser<emUserSetGlobalConfig, cxUserGlobalConfig> cxMSGUserSetGlobalConfig;
typedef cxMSGUser<emUserGetGlobalConfig, cxUserGlobalConfig> cxMSGUserGetGlobalConfig;
typedef cxMSGUser<emUserSetMSGConfig, cxUserMSGConfig> cxMSGUserSetMSGConfig;
typedef cxMSGUser<emUserGetMSGConfig, cxUserMSGConfig> cxMSGUserGetMSGConfig;
typedef cxMSGUser<emUserEnableProtect> cxMSGUserEnableProtect;
typedef cxMSGUser<emUserDisableProtect> cxMSGUserDisableProtect;
typedef cxMSGUser<emUserAddProtectRule, cxUserProtectItem> cxMSGUserAddProtectRule;
typedef cxMSGUser<emUserRemoveProtectRule, cxUserProtectItem> cxMSGUserRemoveProtectRule;
typedef cxMSGUser<emUserRemoveAllProtectRule> cxMSGUserRemoveAllProtectRule;
typedef cxMSGUser<emUserEnumProtectRule> cxMSGUserEnumProtectRule;
//******************************************************************************
#endif
