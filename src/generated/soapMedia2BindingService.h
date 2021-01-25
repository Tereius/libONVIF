/* soapMedia2BindingService.h
   Generated by gSOAP 2.8.88 for generated.h

gSOAP XML Web services tools
Copyright (C) 2000-2018, Robert van Engelen, Genivia Inc. All Rights Reserved.
The soapcpp2 tool and its generated software are released under the GPL.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#ifndef soapMedia2BindingService_H
#define soapMedia2BindingService_H
#include "soapH.h"

    class SOAP_CMAC Media2BindingService {
      public:
        /// Context to manage service IO and data
        struct soap *soap;
        /// flag indicating that this context is owned by this service and should be deleted by the destructor
        bool soap_own;
        /// Variables globally declared in generated.h, if any
        /// Construct a service with new managing context
        Media2BindingService();
        /// Copy constructor
        Media2BindingService(const Media2BindingService&);
        /// Construct service given a shared managing context
        Media2BindingService(struct soap*);
        /// Constructor taking input+output mode flags for the new managing context
        Media2BindingService(soap_mode iomode);
        /// Constructor taking input and output mode flags for the new managing context
        Media2BindingService(soap_mode imode, soap_mode omode);
        /// Destructor deletes deserialized data and its managing context, when the context was allocated by the constructor
        virtual ~Media2BindingService();
        /// Delete all deserialized data (with soap_destroy() and soap_end())
        virtual void destroy();
        /// Delete all deserialized data and reset to defaults
        virtual void reset();
        /// Initializer used by constructors
        virtual void Media2BindingService_init(soap_mode imode, soap_mode omode);
        /// Return a copy that has a new managing context with the same engine state
        virtual Media2BindingService *copy() SOAP_PURE_VIRTUAL_COPY;
        /// Copy assignment
        Media2BindingService& operator=(const Media2BindingService&);
        /// Close connection (normally automatic)
        virtual int soap_close_socket();
        /// Force close connection (can kill a thread blocked on IO)
        virtual int soap_force_close_socket();
        /// Return sender-related fault to sender
        virtual int soap_senderfault(const char *string, const char *detailXML);
        /// Return sender-related fault with SOAP 1.2 subcode to sender
        virtual int soap_senderfault(const char *subcodeQName, const char *string, const char *detailXML);
        /// Return receiver-related fault to sender
        virtual int soap_receiverfault(const char *string, const char *detailXML);
        /// Return receiver-related fault with SOAP 1.2 subcode to sender
        virtual int soap_receiverfault(const char *subcodeQName, const char *string, const char *detailXML);
        /// Print fault
        virtual void soap_print_fault(FILE*);
    #ifndef WITH_LEAN
    #ifndef WITH_COMPAT
        /// Print fault to stream
        virtual void soap_stream_fault(std::ostream&);
    #endif
        /// Write fault to buffer
        virtual char *soap_sprint_fault(char *buf, size_t len);
    #endif
        /// Disables and removes SOAP Header from message by setting soap->header = NULL
        virtual void soap_noheader();
        /// Add SOAP Header to message
        virtual void soap_header(struct _wsse__Security *wsse__Security, char *wsa5__MessageID, struct wsa5__RelatesToType *wsa5__RelatesTo, struct wsa5__EndpointReferenceType *wsa5__From, struct wsa5__EndpointReferenceType *wsa5__ReplyTo, struct wsa5__EndpointReferenceType *wsa5__FaultTo, char *wsa5__To, char *wsa5__Action, struct chan__ChannelInstanceType *chan__ChannelInstance, struct wsdd__AppSequenceType *wsdd__AppSequence);
        /// Get SOAP Header structure (i.e. soap->header, which is NULL when absent)
        virtual ::SOAP_ENV__Header *soap_header();
    #ifndef WITH_NOIO
        /// Run simple single-thread (iterative, non-SSL) service on port until a connection error occurs (returns SOAP_OK or error code), use this->bind_flag = SO_REUSEADDR to rebind for immediate rerun
        virtual int run(int port, int backlog = 1);
    #if defined(WITH_OPENSSL) || defined(WITH_GNUTLS)
        /// Run simple single-thread SSL service on port until a connection error occurs (returns SOAP_OK or error code), use this->bind_flag = SO_REUSEADDR to rebind for immediate rerun
        virtual int ssl_run(int port, int backlog = 1);
    #endif
        /// Bind service to port (returns master socket or SOAP_INVALID_SOCKET upon error)
        virtual SOAP_SOCKET bind(const char *host, int port, int backlog);
        /// Accept next request (returns socket or SOAP_INVALID_SOCKET upon error)
        virtual SOAP_SOCKET accept();
    #if defined(WITH_OPENSSL) || defined(WITH_GNUTLS)
        /// When SSL is used, after accept() should perform and accept SSL handshake
        virtual int ssl_accept();
    #endif
    #endif
        /// After accept() serve the pending request (returns SOAP_OK or error code)
        virtual int serve();
        /// Used by serve() to dispatch a pending request (returns SOAP_OK or error code)
        virtual int dispatch();
        virtual int dispatch(struct soap *soap);
        //
        // Service operations are listed below: you should define these
        // Note: compile with -DWITH_PURE_VIRTUAL to declare pure virtual methods
        //
        /// Web service operation 'GetServiceCapabilities' implementation, should return SOAP_OK or error code
        virtual int GetServiceCapabilities(_tr2__GetServiceCapabilities *tr2__GetServiceCapabilities, _tr2__GetServiceCapabilitiesResponse &tr2__GetServiceCapabilitiesResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'CreateProfile' implementation, should return SOAP_OK or error code
        virtual int CreateProfile(_tr2__CreateProfile *tr2__CreateProfile, _tr2__CreateProfileResponse &tr2__CreateProfileResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'GetProfiles' implementation, should return SOAP_OK or error code
        virtual int GetProfiles(_tr2__GetProfiles *tr2__GetProfiles, _tr2__GetProfilesResponse &tr2__GetProfilesResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'AddConfiguration' implementation, should return SOAP_OK or error code
        virtual int AddConfiguration(_tr2__AddConfiguration *tr2__AddConfiguration, _tr2__AddConfigurationResponse &tr2__AddConfigurationResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'RemoveConfiguration' implementation, should return SOAP_OK or error code
        virtual int RemoveConfiguration(_tr2__RemoveConfiguration *tr2__RemoveConfiguration, _tr2__RemoveConfigurationResponse &tr2__RemoveConfigurationResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'DeleteProfile' implementation, should return SOAP_OK or error code
        virtual int DeleteProfile(_tr2__DeleteProfile *tr2__DeleteProfile, _tr2__DeleteProfileResponse &tr2__DeleteProfileResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'GetVideoSourceConfigurations' implementation, should return SOAP_OK or error code
        virtual int GetVideoSourceConfigurations(tr2__GetConfiguration *tr2__GetVideoSourceConfigurations, _tr2__GetVideoSourceConfigurationsResponse &tr2__GetVideoSourceConfigurationsResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'GetVideoEncoderConfigurations' implementation, should return SOAP_OK or error code
        virtual int GetVideoEncoderConfigurations(tr2__GetConfiguration *tr2__GetVideoEncoderConfigurations, _tr2__GetVideoEncoderConfigurationsResponse &tr2__GetVideoEncoderConfigurationsResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'GetAudioSourceConfigurations' implementation, should return SOAP_OK or error code
        virtual int GetAudioSourceConfigurations(tr2__GetConfiguration *tr2__GetAudioSourceConfigurations, _tr2__GetAudioSourceConfigurationsResponse &tr2__GetAudioSourceConfigurationsResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'GetAudioEncoderConfigurations' implementation, should return SOAP_OK or error code
        virtual int GetAudioEncoderConfigurations(tr2__GetConfiguration *tr2__GetAudioEncoderConfigurations, _tr2__GetAudioEncoderConfigurationsResponse &tr2__GetAudioEncoderConfigurationsResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'GetAnalyticsConfigurations' implementation, should return SOAP_OK or error code
        virtual int GetAnalyticsConfigurations(tr2__GetConfiguration *tr2__GetAnalyticsConfigurations, _tr2__GetAnalyticsConfigurationsResponse &tr2__GetAnalyticsConfigurationsResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'GetMetadataConfigurations' implementation, should return SOAP_OK or error code
        virtual int GetMetadataConfigurations(tr2__GetConfiguration *tr2__GetMetadataConfigurations, _tr2__GetMetadataConfigurationsResponse &tr2__GetMetadataConfigurationsResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'GetAudioOutputConfigurations' implementation, should return SOAP_OK or error code
        virtual int GetAudioOutputConfigurations(tr2__GetConfiguration *tr2__GetAudioOutputConfigurations, _tr2__GetAudioOutputConfigurationsResponse &tr2__GetAudioOutputConfigurationsResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'GetAudioDecoderConfigurations' implementation, should return SOAP_OK or error code
        virtual int GetAudioDecoderConfigurations(tr2__GetConfiguration *tr2__GetAudioDecoderConfigurations, _tr2__GetAudioDecoderConfigurationsResponse &tr2__GetAudioDecoderConfigurationsResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'SetVideoSourceConfiguration' implementation, should return SOAP_OK or error code
        virtual int SetVideoSourceConfiguration(_tr2__SetVideoSourceConfiguration *tr2__SetVideoSourceConfiguration, tr2__SetConfigurationResponse &tr2__SetVideoSourceConfigurationResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'SetVideoEncoderConfiguration' implementation, should return SOAP_OK or error code
        virtual int SetVideoEncoderConfiguration(_tr2__SetVideoEncoderConfiguration *tr2__SetVideoEncoderConfiguration, tr2__SetConfigurationResponse &tr2__SetVideoEncoderConfigurationResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'SetAudioSourceConfiguration' implementation, should return SOAP_OK or error code
        virtual int SetAudioSourceConfiguration(_tr2__SetAudioSourceConfiguration *tr2__SetAudioSourceConfiguration, tr2__SetConfigurationResponse &tr2__SetAudioSourceConfigurationResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'SetAudioEncoderConfiguration' implementation, should return SOAP_OK or error code
        virtual int SetAudioEncoderConfiguration(_tr2__SetAudioEncoderConfiguration *tr2__SetAudioEncoderConfiguration, tr2__SetConfigurationResponse &tr2__SetAudioEncoderConfigurationResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'SetMetadataConfiguration' implementation, should return SOAP_OK or error code
        virtual int SetMetadataConfiguration(_tr2__SetMetadataConfiguration *tr2__SetMetadataConfiguration, tr2__SetConfigurationResponse &tr2__SetMetadataConfigurationResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'SetAudioOutputConfiguration' implementation, should return SOAP_OK or error code
        virtual int SetAudioOutputConfiguration(_tr2__SetAudioOutputConfiguration *tr2__SetAudioOutputConfiguration, tr2__SetConfigurationResponse &tr2__SetAudioOutputConfigurationResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'SetAudioDecoderConfiguration' implementation, should return SOAP_OK or error code
        virtual int SetAudioDecoderConfiguration(_tr2__SetAudioDecoderConfiguration *tr2__SetAudioDecoderConfiguration, tr2__SetConfigurationResponse &tr2__SetAudioDecoderConfigurationResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'GetVideoSourceConfigurationOptions' implementation, should return SOAP_OK or error code
        virtual int GetVideoSourceConfigurationOptions(tr2__GetConfiguration *tr2__GetVideoSourceConfigurationOptions, _tr2__GetVideoSourceConfigurationOptionsResponse &tr2__GetVideoSourceConfigurationOptionsResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'GetVideoEncoderConfigurationOptions' implementation, should return SOAP_OK or error code
        virtual int GetVideoEncoderConfigurationOptions(tr2__GetConfiguration *tr2__GetVideoEncoderConfigurationOptions, _tr2__GetVideoEncoderConfigurationOptionsResponse &tr2__GetVideoEncoderConfigurationOptionsResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'GetAudioSourceConfigurationOptions' implementation, should return SOAP_OK or error code
        virtual int GetAudioSourceConfigurationOptions(tr2__GetConfiguration *tr2__GetAudioSourceConfigurationOptions, _tr2__GetAudioSourceConfigurationOptionsResponse &tr2__GetAudioSourceConfigurationOptionsResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'GetAudioEncoderConfigurationOptions' implementation, should return SOAP_OK or error code
        virtual int GetAudioEncoderConfigurationOptions(tr2__GetConfiguration *tr2__GetAudioEncoderConfigurationOptions, _tr2__GetAudioEncoderConfigurationOptionsResponse &tr2__GetAudioEncoderConfigurationOptionsResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'GetMetadataConfigurationOptions' implementation, should return SOAP_OK or error code
        virtual int GetMetadataConfigurationOptions(tr2__GetConfiguration *tr2__GetMetadataConfigurationOptions, _tr2__GetMetadataConfigurationOptionsResponse &tr2__GetMetadataConfigurationOptionsResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'GetAudioOutputConfigurationOptions' implementation, should return SOAP_OK or error code
        virtual int GetAudioOutputConfigurationOptions(tr2__GetConfiguration *tr2__GetAudioOutputConfigurationOptions, _tr2__GetAudioOutputConfigurationOptionsResponse &tr2__GetAudioOutputConfigurationOptionsResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'GetAudioDecoderConfigurationOptions' implementation, should return SOAP_OK or error code
        virtual int GetAudioDecoderConfigurationOptions(tr2__GetConfiguration *tr2__GetAudioDecoderConfigurationOptions, _tr2__GetAudioDecoderConfigurationOptionsResponse &tr2__GetAudioDecoderConfigurationOptionsResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'GetVideoEncoderInstances' implementation, should return SOAP_OK or error code
        virtual int GetVideoEncoderInstances(_tr2__GetVideoEncoderInstances *tr2__GetVideoEncoderInstances, _tr2__GetVideoEncoderInstancesResponse &tr2__GetVideoEncoderInstancesResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'GetStreamUri' implementation, should return SOAP_OK or error code
        virtual int GetStreamUri(_tr2__GetStreamUri *tr2__GetStreamUri, _tr2__GetStreamUriResponse &tr2__GetStreamUriResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'StartMulticastStreaming' implementation, should return SOAP_OK or error code
        virtual int StartMulticastStreaming(tr2__StartStopMulticastStreaming *tr2__StartMulticastStreaming, tr2__SetConfigurationResponse &tr2__StartMulticastStreamingResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'StopMulticastStreaming' implementation, should return SOAP_OK or error code
        virtual int StopMulticastStreaming(tr2__StartStopMulticastStreaming *tr2__StopMulticastStreaming, tr2__SetConfigurationResponse &tr2__StopMulticastStreamingResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'SetSynchronizationPoint' implementation, should return SOAP_OK or error code
        virtual int SetSynchronizationPoint(_tr2__SetSynchronizationPoint *tr2__SetSynchronizationPoint, _tr2__SetSynchronizationPointResponse &tr2__SetSynchronizationPointResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'GetSnapshotUri' implementation, should return SOAP_OK or error code
        virtual int GetSnapshotUri(_tr2__GetSnapshotUri *tr2__GetSnapshotUri, _tr2__GetSnapshotUriResponse &tr2__GetSnapshotUriResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'GetVideoSourceModes' implementation, should return SOAP_OK or error code
        virtual int GetVideoSourceModes(_tr2__GetVideoSourceModes *tr2__GetVideoSourceModes, _tr2__GetVideoSourceModesResponse &tr2__GetVideoSourceModesResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'SetVideoSourceMode' implementation, should return SOAP_OK or error code
        virtual int SetVideoSourceMode(_tr2__SetVideoSourceMode *tr2__SetVideoSourceMode, _tr2__SetVideoSourceModeResponse &tr2__SetVideoSourceModeResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'GetOSDs' implementation, should return SOAP_OK or error code
        virtual int GetOSDs(_tr2__GetOSDs *tr2__GetOSDs, _tr2__GetOSDsResponse &tr2__GetOSDsResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'GetOSDOptions' implementation, should return SOAP_OK or error code
        virtual int GetOSDOptions(_tr2__GetOSDOptions *tr2__GetOSDOptions, _tr2__GetOSDOptionsResponse &tr2__GetOSDOptionsResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'SetOSD' implementation, should return SOAP_OK or error code
        virtual int SetOSD(_tr2__SetOSD *tr2__SetOSD, tr2__SetConfigurationResponse &tr2__SetOSDResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'CreateOSD' implementation, should return SOAP_OK or error code
        virtual int CreateOSD(_tr2__CreateOSD *tr2__CreateOSD, _tr2__CreateOSDResponse &tr2__CreateOSDResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'DeleteOSD' implementation, should return SOAP_OK or error code
        virtual int DeleteOSD(_tr2__DeleteOSD *tr2__DeleteOSD, tr2__SetConfigurationResponse &tr2__DeleteOSDResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'GetMasks' implementation, should return SOAP_OK or error code
        virtual int GetMasks(_tr2__GetMasks *tr2__GetMasks, _tr2__GetMasksResponse &tr2__GetMasksResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'GetMaskOptions' implementation, should return SOAP_OK or error code
        virtual int GetMaskOptions(_tr2__GetMaskOptions *tr2__GetMaskOptions, _tr2__GetMaskOptionsResponse &tr2__GetMaskOptionsResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'SetMask' implementation, should return SOAP_OK or error code
        virtual int SetMask(_tr2__SetMask *tr2__SetMask, tr2__SetConfigurationResponse &tr2__SetMaskResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'CreateMask' implementation, should return SOAP_OK or error code
        virtual int CreateMask(_tr2__CreateMask *tr2__CreateMask, _tr2__CreateMaskResponse &tr2__CreateMaskResponse) SOAP_PURE_VIRTUAL;
        //
        /// Web service operation 'DeleteMask' implementation, should return SOAP_OK or error code
        virtual int DeleteMask(_tr2__DeleteMask *tr2__DeleteMask, tr2__SetConfigurationResponse &tr2__DeleteMaskResponse) SOAP_PURE_VIRTUAL;
    };
#endif
