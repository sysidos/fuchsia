// WARNING: This file is machine generated by fidlgen.

#pragma once

#include <lib/fidl/internal.h>
#include <lib/fidl/txn_header.h>
#include <lib/fidl/llcpp/array.h>
#include <lib/fidl/llcpp/coding.h>
#include <lib/fidl/llcpp/connect_service.h>
#include <lib/fidl/llcpp/service_handler_interface.h>
#include <lib/fidl/llcpp/string_view.h>
#include <lib/fidl/llcpp/sync_call.h>
#include <lib/fidl/llcpp/traits.h>
#include <lib/fidl/llcpp/transaction.h>
#include <lib/fidl/llcpp/vector_view.h>
#include <lib/fit/function.h>
#include <lib/zx/channel.h>
#include <zircon/fidl.h>

#include <fuchsia/tee/llcpp/fidl.h>
#include <fuchsia/tee/manager/llcpp/fidl.h>

namespace llcpp {

namespace fuchsia {
namespace hardware {
namespace tee {

class DeviceConnector;

extern "C" const fidl_type_t fuchsia_hardware_tee_DeviceConnectorConnectTeeRequestTable;
extern "C" const fidl_type_t v1_fuchsia_hardware_tee_DeviceConnectorConnectTeeRequestTable;
extern "C" const fidl_type_t fuchsia_hardware_tee_DeviceConnectorConnectTeeResponseTable;
extern "C" const fidl_type_t v1_fuchsia_hardware_tee_DeviceConnectorConnectTeeResponseTable;

// Protocol used by the TEE Manager to proxy requests for TEE access to the driver.
class DeviceConnector final {
  DeviceConnector() = delete;
 public:

  struct ConnectTeeRequest final {
    FIDL_ALIGNDECL
    fidl_message_header_t _hdr;
    ::zx::channel service_provider;
    ::zx::channel tee_request;

    static constexpr const fidl_type_t* Type = &v1_fuchsia_hardware_tee_DeviceConnectorConnectTeeRequestTable;
    static constexpr const fidl_type_t* AltType = &fuchsia_hardware_tee_DeviceConnectorConnectTeeRequestTable;
    static constexpr uint32_t MaxNumHandles = 2;
    static constexpr uint32_t PrimarySize = 24;
    static constexpr uint32_t MaxOutOfLine = 0;
    static constexpr uint32_t AltPrimarySize = 24;
    static constexpr uint32_t AltMaxOutOfLine = 0;
    static constexpr bool HasFlexibleEnvelope = false;
    static constexpr bool HasPointer = false;
    static constexpr bool ContainsUnion = false;
    static constexpr ::fidl::internal::TransactionalMessageKind MessageKind =
        ::fidl::internal::TransactionalMessageKind::kRequest;
  };


  // Collection of return types of FIDL calls in this interface.
  class ResultOf final {
    ResultOf() = delete;
   private:
    class ConnectTee_Impl final : private ::fidl::internal::StatusAndError {
      using Super = ::fidl::internal::StatusAndError;
     public:
      ConnectTee_Impl(::zx::unowned_channel _client_end, ::zx::channel service_provider, ::zx::channel tee_request);
      ~ConnectTee_Impl() = default;
      ConnectTee_Impl(ConnectTee_Impl&& other) = default;
      ConnectTee_Impl& operator=(ConnectTee_Impl&& other) = default;
      using Super::status;
      using Super::error;
      using Super::ok;
    };

   public:
    using ConnectTee = ConnectTee_Impl;
  };

  // Collection of return types of FIDL calls in this interface,
  // when the caller-allocate flavor or in-place call is used.
  class UnownedResultOf final {
    UnownedResultOf() = delete;
   private:
    class ConnectTee_Impl final : private ::fidl::internal::StatusAndError {
      using Super = ::fidl::internal::StatusAndError;
     public:
      ConnectTee_Impl(::zx::unowned_channel _client_end, ::fidl::BytePart _request_buffer, ::zx::channel service_provider, ::zx::channel tee_request);
      ~ConnectTee_Impl() = default;
      ConnectTee_Impl(ConnectTee_Impl&& other) = default;
      ConnectTee_Impl& operator=(ConnectTee_Impl&& other) = default;
      using Super::status;
      using Super::error;
      using Super::ok;
    };

   public:
    using ConnectTee = ConnectTee_Impl;
  };

  class SyncClient final {
   public:
    explicit SyncClient(::zx::channel channel) : channel_(std::move(channel)) {}
    ~SyncClient() = default;
    SyncClient(SyncClient&&) = default;
    SyncClient& operator=(SyncClient&&) = default;

    const ::zx::channel& channel() const { return channel_; }

    ::zx::channel* mutable_channel() { return &channel_; }

    // Requests service from the TEE driver while the caller provides a client end to a
    // Provider server that supports the driver on any RPCs.
    //
    // The sole caller of this should be the TEE Manager.
    // Allocates 24 bytes of message buffer on the stack. No heap allocation necessary.
    ResultOf::ConnectTee ConnectTee(::zx::channel service_provider, ::zx::channel tee_request);

    // Requests service from the TEE driver while the caller provides a client end to a
    // Provider server that supports the driver on any RPCs.
    //
    // The sole caller of this should be the TEE Manager.
    // Caller provides the backing storage for FIDL message via request and response buffers.
    UnownedResultOf::ConnectTee ConnectTee(::fidl::BytePart _request_buffer, ::zx::channel service_provider, ::zx::channel tee_request);

   private:
    ::zx::channel channel_;
  };

  // Methods to make a sync FIDL call directly on an unowned channel, avoiding setting up a client.
  class Call final {
    Call() = delete;
   public:

    // Requests service from the TEE driver while the caller provides a client end to a
    // Provider server that supports the driver on any RPCs.
    //
    // The sole caller of this should be the TEE Manager.
    // Allocates 24 bytes of message buffer on the stack. No heap allocation necessary.
    static ResultOf::ConnectTee ConnectTee(::zx::unowned_channel _client_end, ::zx::channel service_provider, ::zx::channel tee_request);

    // Requests service from the TEE driver while the caller provides a client end to a
    // Provider server that supports the driver on any RPCs.
    //
    // The sole caller of this should be the TEE Manager.
    // Caller provides the backing storage for FIDL message via request and response buffers.
    static UnownedResultOf::ConnectTee ConnectTee(::zx::unowned_channel _client_end, ::fidl::BytePart _request_buffer, ::zx::channel service_provider, ::zx::channel tee_request);

  };

  // Messages are encoded and decoded in-place when these methods are used.
  // Additionally, requests must be already laid-out according to the FIDL wire-format.
  class InPlace final {
    InPlace() = delete;
   public:

    // Requests service from the TEE driver while the caller provides a client end to a
    // Provider server that supports the driver on any RPCs.
    //
    // The sole caller of this should be the TEE Manager.
    static ::fidl::internal::StatusAndError ConnectTee(::zx::unowned_channel _client_end, ::fidl::DecodedMessage<ConnectTeeRequest> params);

  };

  // Pure-virtual interface to be implemented by a server.
  class Interface {
   public:
    Interface() = default;
    virtual ~Interface() = default;
    using _Outer = DeviceConnector;
    using _Base = ::fidl::CompleterBase;

    using ConnectTeeCompleter = ::fidl::Completer<>;

    virtual void ConnectTee(::zx::channel service_provider, ::zx::channel tee_request, ConnectTeeCompleter::Sync _completer) = 0;

  };

  // Attempts to dispatch the incoming message to a handler function in the server implementation.
  // If there is no matching handler, it returns false, leaving the message and transaction intact.
  // In all other cases, it consumes the message and returns true.
  // It is possible to chain multiple TryDispatch functions in this manner.
  static bool TryDispatch(Interface* impl, fidl_msg_t* msg, ::fidl::Transaction* txn);

  // Dispatches the incoming message to one of the handlers functions in the interface.
  // If there is no matching handler, it closes all the handles in |msg| and closes the channel with
  // a |ZX_ERR_NOT_SUPPORTED| epitaph, before returning false. The message should then be discarded.
  static bool Dispatch(Interface* impl, fidl_msg_t* msg, ::fidl::Transaction* txn);

  // Same as |Dispatch|, but takes a |void*| instead of |Interface*|. Only used with |fidl::Bind|
  // to reduce template expansion.
  // Do not call this method manually. Use |Dispatch| instead.
  static bool TypeErasedDispatch(void* impl, fidl_msg_t* msg, ::fidl::Transaction* txn) {
    return Dispatch(static_cast<Interface*>(impl), msg, txn);
  }


  // Helper functions to fill in the transaction header in a |DecodedMessage<TransactionalMessage>|.
  class SetTransactionHeaderFor final {
    SetTransactionHeaderFor() = delete;
   public:
    static void ConnectTeeRequest(const ::fidl::DecodedMessage<DeviceConnector::ConnectTeeRequest>& _msg);
  };
};

}  // namespace tee
}  // namespace hardware
}  // namespace fuchsia
}  // namespace llcpp

namespace fidl {

template <>
struct IsFidlType<::llcpp::fuchsia::hardware::tee::DeviceConnector::ConnectTeeRequest> : public std::true_type {};
template <>
struct IsFidlMessage<::llcpp::fuchsia::hardware::tee::DeviceConnector::ConnectTeeRequest> : public std::true_type {};
static_assert(sizeof(::llcpp::fuchsia::hardware::tee::DeviceConnector::ConnectTeeRequest)
    == ::llcpp::fuchsia::hardware::tee::DeviceConnector::ConnectTeeRequest::PrimarySize);
static_assert(offsetof(::llcpp::fuchsia::hardware::tee::DeviceConnector::ConnectTeeRequest, service_provider) == 16);
static_assert(offsetof(::llcpp::fuchsia::hardware::tee::DeviceConnector::ConnectTeeRequest, tee_request) == 20);

}  // namespace fidl
