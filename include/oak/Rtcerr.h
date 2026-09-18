/*
 * Rtcerr.h -- RTC Client API return values (RTC_E_ / RTC_S_) for
 * Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Every value is printed on its official page: RTC_E_ constants on
 * ms931795 "RTC_E_ (Windows CE 5.0)" (CE .NET 4.0+; Header: Rtcerr.h),
 * the CE 6.0 twin ee499276, and RTC_S_ on ms912578 / ee500988.  The
 * pages print the HRESULT layout (Sev|C|R|Facility|Code; facility EE =
 * RTC interface codes, EF = SIP status codes, F0 = PINT status codes).
 * Moved out of Rtccore.h so that the documented "Header: Rtcerr.h"
 * spelling resolves (Rtccore.h includes this file).
 */
#ifndef AKARI_RTCERR_H
#define AKARI_RTCERR_H

/* RTC_E_ (ms931795, ee499276): values printed on the pages. */
#define RTC_E_ANOTHER_MEDIA_SESSION_ACTIVE              0x80EE0077L
#define RTC_E_BASIC_AUTH_SET_TLS                        0x80EE003FL
#define RTC_E_CLIENT_ALREADY_INITIALIZED                0x80EE0026L
#define RTC_E_CLIENT_ALREADY_SHUT_DOWN                  0x80EE0027L
#define RTC_E_CLIENT_NOT_INITIALIZED                    0x80EE0025L
#define RTC_E_DESTINATION_ADDRESS_LOCAL                 0x80EE0013L
#define RTC_E_DESTINATION_ADDRESS_MULTICAST             0x80EE0015L
#define RTC_E_DUPLICATE_BUDDY                           0x80EE004AL
#define RTC_E_DUPLICATE_GROUP                           0x80EE0052L
#define RTC_E_DUPLICATE_REALM                           0x80EE0043L
#define RTC_E_DUPLICATE_WATCHER                         0x80EE004BL
#define RTC_E_INSUFFICIENT_SECURITY_LEVEL               0x80EE0047L
#define RTC_E_INVALID_ACL_LIST                          0x80EE0050L
#define RTC_E_INVALID_ADDRESS_LOCAL                     0x80EE0014L
#define RTC_E_INVALID_BUDDY_LIST                        0x80EE004FL
#define RTC_E_INVALID_LISTEN_SOCKET                     0x80EE007BL
#define RTC_E_INVALID_OBJECT_STATE                      0x80EE0061L
#define RTC_E_INVALID_PORTRANGE                         0x80EE005CL
#define RTC_E_INVALID_PREFERENCE_LIST                   0x80EE0059L
#define RTC_E_INVALID_PROFILE                           0x80EE002EL
#define RTC_E_INVALID_PROXY_ADDRESS                     0x80EE0016L
#define RTC_E_INVALID_REGISTRATION_STATE                0x80EE006DL
#define RTC_E_INVALID_SESSION_STATE                     0x80EE002AL
#define RTC_E_INVALID_SESSION_TYPE                      0x80EE0029L
#define RTC_E_INVALID_SIP_URL                           0x80EE0012L
#define RTC_E_INVITEE_PARTY_TIMEOUT                     0x80EE006BL
#define RTC_E_LISTENING_SOCKET_NOT_EXIST                0x80EE007AL
#define RTC_E_LOCAL_PHONE_NEEDED                        0x80EE002CL
#define RTC_E_MALFORMED_XML                             0x80EE004CL
#define RTC_E_MAX_PENDING_OPERATIONS                    0x80EE005AL
#define RTC_E_MAX_REDIRECTS                             0x80EE0078L
#define RTC_E_MEDIA_AEC                                 0x80EE0024L
#define RTC_E_MEDIA_AUDIO_DEVICE_NOT_AVAILABLE          0x80EE0021L
#define RTC_E_MEDIA_CONTROLLER_STATE                    0x80EE001FL
#define RTC_E_MEDIA_DISABLED                            0x80EE006EL
#define RTC_E_MEDIA_ENABLED                             0x80EE006FL
#define RTC_E_MEDIA_NEED_TERMINAL                       0x80EE0020L
#define RTC_E_MEDIA_SESSION_IN_HOLD                     0x80EE0076L
#define RTC_E_MEDIA_SESSION_NOT_EXIST                   0x80EE0075L
#define RTC_E_MEDIA_VIDEO_DEVICE_NOT_AVAILABLE          0x80EE0022L
#define RTC_E_NOT_EXIST                                 0x80EE0058L
#define RTC_E_NOT_PRESENCE_PROFILE                      0x80EE006AL
#define RTC_E_NO_BUDDY                                  0x80EE0054L
#define RTC_E_NO_DEVICE                                 0x80EE002DL
#define RTC_E_NO_GROUP                                  0x80EE0051L
#define RTC_E_NO_PROFILE                                0x80EE002BL
#define RTC_E_NO_REALM                                  0x80EE0056L
#define RTC_E_NO_TRANSPORT                              0x80EE0057L
#define RTC_E_NO_WATCHER                                0x80EE0055L
#define RTC_E_PINT_STATUS_REJECTED_ALL_BUSY             0x80F00007L
#define RTC_E_PINT_STATUS_REJECTED_BADNUMBER            0x80F0000BL
#define RTC_E_PINT_STATUS_REJECTED_BUSY                 0x80F00005L
#define RTC_E_PINT_STATUS_REJECTED_CANCELLED            0x80F0000AL
#define RTC_E_PINT_STATUS_REJECTED_NO_ANSWER            0x80F00006L
#define RTC_E_PINT_STATUS_REJECTED_PL_FAILED            0x80F00008L
#define RTC_E_PINT_STATUS_REJECTED_SW_FAILED            0x80F00009L
#define RTC_E_POLICY_NOT_ALLOW                          0x80EE0044L
#define RTC_E_PORT_MANAGER_ALREADY_SET                  0x80EE007CL
#define RTC_E_PORT_MAPPING_FAILED                       0x80EE0046L
#define RTC_E_PORT_MAPPING_UNAVAILABLE                  0x80EE0045L
#define RTC_E_PRESENCE_ENABLED                          0x80EE0062L
#define RTC_E_PRESENCE_NOT_ENABLED                      0x80EE0028L
#define RTC_E_PROFILE_INVALID_SERVER_AUTHMETHOD         0x80EE0038L
#define RTC_E_PROFILE_INVALID_SERVER_PROTOCOL           0x80EE0037L
#define RTC_E_PROFILE_INVALID_SERVER_ROLE               0x80EE0039L
#define RTC_E_PROFILE_INVALID_SESSION                   0x80EE003BL
#define RTC_E_PROFILE_INVALID_SESSION_PARTY             0x80EE003CL
#define RTC_E_PROFILE_INVALID_SESSION_TYPE              0x80EE003DL
#define RTC_E_PROFILE_MULTIPLE_REGISTRARS               0x80EE003AL
#define RTC_E_PROFILE_NO_KEY                            0x80EE0030L
#define RTC_E_PROFILE_NO_NAME                           0x80EE0031L
#define RTC_E_PROFILE_NO_PROVISION                      0x80EE002FL
#define RTC_E_PROFILE_NO_SERVER                         0x80EE0034L
#define RTC_E_PROFILE_NO_SERVER_ADDRESS                 0x80EE0035L
#define RTC_E_PROFILE_NO_SERVER_PROTOCOL                0x80EE0036L
#define RTC_E_PROFILE_NO_USER                           0x80EE0032L
#define RTC_E_PROFILE_NO_USER_URI                       0x80EE0033L
#define RTC_E_PROFILE_SERVER_UNAUTHORIZED               0x80EE0042L
#define RTC_E_REDIRECT_PROCESSING_FAILED                0x80EE0079L
#define RTC_E_REFER_NOT_ACCEPTED                        0x80EE0070L
#define RTC_E_REFER_NOT_ALLOWED                         0x80EE0071L
#define RTC_E_REFER_NOT_EXIST                           0x80EE0072L
#define RTC_E_REGISTRATION_DEACTIVATED                  0x80EE0083L
#define RTC_E_REGISTRATION_REJECTED                     0x80EE0084L
#define RTC_E_REGISTRATION_UNREGISTERED                 0x80EE0085L
#define RTC_E_ROAMING_ENABLED                           0x80EE0063L
#define RTC_E_ROAMING_FAILED                            0x80EE004EL
#define RTC_E_ROAMING_OPERATION_INTERRUPTED             0x80EE004DL
#define RTC_E_SDP_CONNECTION_ADDR                       0x80EE000AL
#define RTC_E_SDP_FAILED_TO_BUILD                       0x80EE000DL
#define RTC_E_SDP_MULTICAST                             0x80EE0009L
#define RTC_E_SDP_NOT_PRESENT                           0x80EE0006L
#define RTC_E_SDP_NO_MEDIA                              0x80EE000BL
#define RTC_E_SDP_PARSE_FAILED                          0x80EE0007L
#define RTC_E_SDP_UPDATE_FAILED                         0x80EE0008L
#define RTC_E_SECURITY_LEVEL_NOT_COMPATIBLE             0x80EE007DL
#define RTC_E_SECURITY_LEVEL_NOT_DEFINED                0x80EE0048L
#define RTC_E_SECURITY_LEVEL_NOT_SUPPORTED_BY_PARTICIPANT 0x80EE0049L
#define RTC_E_SIP_ADDITIONAL_PARTY_IN_TWO_PARTY_SESSION 0x80EE005EL
#define RTC_E_SIP_AUTH_FAILED                           0x80EE0011L
#define RTC_E_SIP_AUTH_HEADER_SENT                      0x80EE000FL
#define RTC_E_SIP_AUTH_TIME_SKEW                        0x80EE006CL
#define RTC_E_SIP_AUTH_TYPE_NOT_SUPPORTED               0x80EE0010L
#define RTC_E_SIP_CALL_CONNECTION_NOT_ESTABLISHED       0x80EE005DL
#define RTC_E_SIP_CALL_DISCONNECTED                     0x80EE0019L
#define RTC_E_SIP_CODECS_DO_NOT_MATCH                   0x80EE0000L
#define RTC_E_SIP_DNS_FAIL                              0x80EE0066L
#define RTC_E_SIP_HEADER_NOT_PRESENT                    0x80EE0005L
#define RTC_E_SIP_HIGH_SECURITY_SET_TLS                 0x80EE0040L
#define RTC_E_SIP_HOLD_OPERATION_PENDING                0x80EE0073L
#define RTC_E_SIP_INCOMPATIBLE_ENCRYPTION               0x80EE0064L
#define RTC_E_SIP_INVALID_CERTIFICATE                   0x80EE0065L
#define RTC_E_SIP_INVITE_TRANSACTION_PENDING            0x80EE000EL
#define RTC_E_SIP_NEED_MORE_DATA                        0x80EE0018L
#define RTC_E_SIP_NO_STREAM                             0x80EE0003L
#define RTC_E_SIP_OTHER_PARTY_JOIN_IN_PROGRESS          0x80EE0060L
#define RTC_E_SIP_PARSE_FAILED                          0x80EE0004L
#define RTC_E_SIP_PARTY_ALREADY_IN_SESSION              0x80EE005FL
#define RTC_E_SIP_REQUEST_DESTINATION_ADDR_NOT_PRESENT  0x80EE001AL
#define RTC_E_SIP_SSL_NEGOTIATION_TIMEOUT               0x80EE001DL
#define RTC_E_SIP_SSL_TUNNEL_FAILED                     0x80EE001CL
#define RTC_E_SIP_STACK_SHUTDOWN                        0x80EE001EL
#define RTC_E_SIP_STREAM_NOT_PRESENT                    0x80EE0002L
#define RTC_E_SIP_STREAM_PRESENT                        0x80EE0001L
#define RTC_E_SIP_TCP_FAIL                              0x80EE0067L
#define RTC_E_SIP_TIMEOUT                               0x80EE000CL
#define RTC_E_SIP_TLS_FAIL                              0x80EE0069L
#define RTC_E_SIP_TRANSPORT_NOT_SUPPORTED               0x80EE0017L
#define RTC_E_SIP_UDP_SIZE_EXCEEDED                     0x80EE001BL
#define RTC_E_SIP_UNHOLD_OPERATION_PENDING              0x80EE0074L
#define RTC_E_START_STREAM                              0x80EE0023L
#define RTC_E_STATUS_CLIENT_ADDRESS_INCOMPLETE          0x80EF01E4L
#define RTC_E_STATUS_CLIENT_AMBIGUOUS                   0x80EF01E5L
#define RTC_E_STATUS_CLIENT_BAD_EXTENSION               0x80EF01A4L
#define RTC_E_STATUS_CLIENT_BAD_REQUEST                 0x80EF0190L
#define RTC_E_STATUS_CLIENT_BUSY_HERE                   0x80EF01E6L
#define RTC_E_STATUS_CLIENT_CONFLICT                    0x80EF0199L
#define RTC_E_STATUS_CLIENT_FORBIDDEN                   0x80EF0193L
#define RTC_E_STATUS_CLIENT_GONE                        0x80EF019AL
#define RTC_E_STATUS_CLIENT_LENGTH_REQUIRED             0x80EF019BL
#define RTC_E_STATUS_CLIENT_LOOP_DETECTED               0x80EF01E2L
#define RTC_E_STATUS_CLIENT_METHOD_NOT_ALLOWED          0x80EF0195L
#define RTC_E_STATUS_CLIENT_NOT_ACCEPTABLE              0x80EF0196L
#define RTC_E_STATUS_CLIENT_NOT_FOUND                   0x80EF0194L
#define RTC_E_STATUS_CLIENT_PAYMENT_REQUIRED            0x80EF0192L
#define RTC_E_STATUS_CLIENT_PROXY_AUTHENTICATION_REQUIRED 0x80EF0197L
#define RTC_E_STATUS_CLIENT_REQUEST_ENTITY_TOO_LARGE    0x80EF019DL
#define RTC_E_STATUS_CLIENT_REQUEST_TIMEOUT             0x80EF0198L
#define RTC_E_STATUS_CLIENT_REQUEST_URI_TOO_LARGE       0x80EF019EL
#define RTC_E_STATUS_CLIENT_TEMPORARILY_NOT_AVAILABLE   0x80EF01E0L
#define RTC_E_STATUS_CLIENT_TOO_MANY_HOPS               0x80EF01E3L
#define RTC_E_STATUS_CLIENT_TRANSACTION_DOES_NOT_EXIST  0x80EF01E1L
#define RTC_E_STATUS_CLIENT_UNAUTHORIZED                0x80EF0191L
#define RTC_E_STATUS_CLIENT_UNSUPPORTED_MEDIA_TYPE      0x80EF019FL
#define RTC_E_STATUS_GLOBAL_BUSY_EVERYWHERE             0x80EF0258L
#define RTC_E_STATUS_GLOBAL_DECLINE                     0x80EF025BL
#define RTC_E_STATUS_GLOBAL_DOES_NOT_EXIST_ANYWHERE     0x80EF025CL
#define RTC_E_STATUS_GLOBAL_NOT_ACCEPTABLE              0x80EF025EL
#define RTC_E_STATUS_INFO_CALL_FORWARDING               0x00EF00B5L
#define RTC_E_STATUS_INFO_QUEUED                        0x00EF00B6L
#define RTC_E_STATUS_INFO_RINGING                       0x00EF00B4L
#define RTC_E_STATUS_INFO_TRYING                        0x00EF0064L
#define RTC_E_STATUS_NOT_ACCEPTABLE_HERE                0x80EF01E8L
#define RTC_E_STATUS_REDIRECT_ALTERNATIVE_SERVICE       0x80EF017CL
#define RTC_E_STATUS_REDIRECT_MOVED_PERMANENTLY         0x80EF012DL
#define RTC_E_STATUS_REDIRECT_MOVED_TEMPORARILY         0x80EF012EL
#define RTC_E_STATUS_REDIRECT_MULTIPLE_CHOICES          0x80EF012CL
#define RTC_E_STATUS_REDIRECT_SEE_OTHER                 0x80EF012FL
#define RTC_E_STATUS_REDIRECT_USE_PROXY                 0x80EF0131L
#define RTC_E_STATUS_REQUEST_TERMINATED                 0x80EF01E7L
#define RTC_E_STATUS_SERVER_BAD_GATEWAY                 0x80EF01F6L
#define RTC_E_STATUS_SERVER_INTERNAL_ERROR              0x80EF01F4L
#define RTC_E_STATUS_SERVER_NOT_IMPLEMENTED             0x80EF01F5L
#define RTC_E_STATUS_SERVER_SERVER_TIMEOUT              0x80EF01F8L
#define RTC_E_STATUS_SERVER_SERVICE_UNAVAILABLE         0x80EF01F7L
#define RTC_E_STATUS_SERVER_VERSION_NOT_SUPPORTED       0x80EF01F9L
#define RTC_E_STATUS_SESSION_PROGRESS                   0x00EF00B7L
#define RTC_E_STATUS_SUCCESS                            0x00EF00C8L
#define RTC_E_TOO_MANY_GROUPS                           0x80EE0053L
#define RTC_E_TOO_MANY_RETRIES                          0x80EE005BL
#define RTC_E_TOO_SMALL_EXPIRES_VALUE                   0x80EE0068L

#if _WIN32_WCE >= 0x0600   /* documented on the CE 6.0 page only (ee499276) */
#define RTC_E_INVALID_SUBSCRIPTION_STATE                0x80EE0090L/* ee499276 */
#endif /* _WIN32_WCE >= 0x0600 */

/* RTC_S_ (ms912578, ee500988): values printed on the pages. */
#define RTC_S_ROAMING_NOT_SUPPORTED                     0x80EE0041L

#endif /* AKARI_RTCERR_H */
