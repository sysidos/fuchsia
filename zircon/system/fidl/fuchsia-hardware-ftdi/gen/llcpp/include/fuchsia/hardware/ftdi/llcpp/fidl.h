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

namespace llcpp {

namespace fuchsia {
namespace hardware {
namespace ftdi {

struct I2cDevice;
struct I2cBusLayout;
class Device;

extern "C" const fidl_type_t fuchsia_hardware_ftdi_I2cDeviceTable;
extern "C" const fidl_type_t v1_fuchsia_hardware_ftdi_I2cDeviceTable;

// Each one of these represents an I2cDevice that will exist
// on the newly created bus. The I2C bus will try and bind
// a driver on the bus with the given VID, PID, DID.
struct I2cDevice {
  static constexpr const fidl_type_t* Type = &v1_fuchsia_hardware_ftdi_I2cDeviceTable;
  static constexpr uint32_t MaxNumHandles = 0;
  static constexpr uint32_t PrimarySize = 16;
  [[maybe_unused]]
  static constexpr uint32_t MaxOutOfLine = 0;
  static constexpr bool HasPointer = false;

  uint32_t address = {};

  uint32_t vid = {};

  uint32_t pid = {};

  uint32_t did = {};
};

extern "C" const fidl_type_t fuchsia_hardware_ftdi_I2cBusLayoutTable;
extern "C" const fidl_type_t v1_fuchsia_hardware_ftdi_I2cBusLayoutTable;

// This represents the data necessary for the FTDI device
// to create an I2C bus.
struct I2cBusLayout {
  static constexpr const fidl_type_t* Type = &v1_fuchsia_hardware_ftdi_I2cBusLayoutTable;
  static constexpr uint32_t MaxNumHandles = 0;
  static constexpr uint32_t PrimarySize = 12;
  [[maybe_unused]]
  static constexpr uint32_t MaxOutOfLine = 0;
  static constexpr bool HasPointer = false;

  uint32_t scl = {};

  // The FTDI needs two pins to be able to drive input and output for
  // SDA. Please specify the two pins here. They *must* be physically
  // tied together on the board with a jumper wire.
  uint32_t sda_out = {};

  uint32_t sda_in = {};
};

extern "C" const fidl_type_t fuchsia_hardware_ftdi_DeviceCreateI2CRequestTable;
extern "C" const fidl_type_t v1_fuchsia_hardware_ftdi_DeviceCreateI2CRequestTable;
extern "C" const fidl_type_t fuchsia_hardware_ftdi_DeviceCreateI2CResponseTable;
extern "C" const fidl_type_t v1_fuchsia_hardware_ftdi_DeviceCreateI2CResponseTable;

class Device final {
  Device() = delete;
 public:

  struct CreateI2CRequest final {
    FIDL_ALIGNDECL
    fidl_message_header_t _hdr;
    ::llcpp::fuchsia::hardware::ftdi::I2cBusLayout layout;
    ::llcpp::fuchsia::hardware::ftdi::I2cDevice device;

    static constexpr const fidl_type_t* Type = &v1_fuchsia_hardware_ftdi_DeviceCreateI2CRequestTable;
    static constexpr const fidl_type_t* AltType = &fuchsia_hardware_ftdi_DeviceCreateI2CRequestTable;
    static constexpr uint32_t MaxNumHandles = 0;
    static constexpr uint32_t PrimarySize = 48;
    static constexpr uint32_t MaxOutOfLine = 0;
    static constexpr uint32_t AltPrimarySize = 48;
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
    class CreateI2C_Impl final : private ::fidl::internal::StatusAndError {
      using Super = ::fidl::internal::StatusAndError;
     public:
      CreateI2C_Impl(::zx::unowned_channel _client_end, ::llcpp::fuchsia::hardware::ftdi::I2cBusLayout layout, ::llcpp::fuchsia::hardware::ftdi::I2cDevice device);
      ~CreateI2C_Impl() = default;
      CreateI2C_Impl(CreateI2C_Impl&& other) = default;
      CreateI2C_Impl& operator=(CreateI2C_Impl&& other) = default;
      using Super::status;
      using Super::error;
      using Super::ok;
    };

   public:
    using CreateI2C = CreateI2C_Impl;
  };

  // Collection of return types of FIDL calls in this interface,
  // when the caller-allocate flavor or in-place call is used.
  class UnownedResultOf final {
    UnownedResultOf() = delete;
   private:
    class CreateI2C_Impl final : private ::fidl::internal::StatusAndError {
      using Super = ::fidl::internal::StatusAndError;
     public:
      CreateI2C_Impl(::zx::unowned_channel _client_end, ::fidl::BytePart _request_buffer, ::llcpp::fuchsia::hardware::ftdi::I2cBusLayout layout, ::llcpp::fuchsia::hardware::ftdi::I2cDevice device);
      ~CreateI2C_Impl() = default;
      CreateI2C_Impl(CreateI2C_Impl&& other) = default;
      CreateI2C_Impl& operator=(CreateI2C_Impl&& other) = default;
      using Super::status;
      using Super::error;
      using Super::ok;
    };

   public:
    using CreateI2C = CreateI2C_Impl;
  };

  class SyncClient final {
   public:
    explicit SyncClient(::zx::channel channel) : channel_(std::move(channel)) {}
    ~SyncClient() = default;
    SyncClient(SyncClient&&) = default;
    SyncClient& operator=(SyncClient&&) = default;

    const ::zx::channel& channel() const { return channel_; }

    ::zx::channel* mutable_channel() { return &channel_; }

    // Create an I2c bus on the FTDI device with a given `layout` and
    // with `device` attached to it.
    // Allocates 48 bytes of message buffer on the stack. No heap allocation necessary.
    ResultOf::CreateI2C CreateI2C(::llcpp::fuchsia::hardware::ftdi::I2cBusLayout layout, ::llcpp::fuchsia::hardware::ftdi::I2cDevice device);

    // Create an I2c bus on the FTDI device with a given `layout` and
    // with `device` attached to it.
    // Caller provides the backing storage for FIDL message via request and response buffers.
    UnownedResultOf::CreateI2C CreateI2C(::fidl::BytePart _request_buffer, ::llcpp::fuchsia::hardware::ftdi::I2cBusLayout layout, ::llcpp::fuchsia::hardware::ftdi::I2cDevice device);

   private:
    ::zx::channel channel_;
  };

  // Methods to make a sync FIDL call directly on an unowned channel, avoiding setting up a client.
  class Call final {
    Call() = delete;
   public:

    // Create an I2c bus on the FTDI device with a given `layout` and
    // with `device` attached to it.
    // Allocates 48 bytes of message buffer on the stack. No heap allocation necessary.
    static ResultOf::CreateI2C CreateI2C(::zx::unowned_channel _client_end, ::llcpp::fuchsia::hardware::ftdi::I2cBusLayout layout, ::llcpp::fuchsia::hardware::ftdi::I2cDevice device);

    // Create an I2c bus on the FTDI device with a given `layout` and
    // with `device` attached to it.
    // Caller provides the backing storage for FIDL message via request and response buffers.
    static UnownedResultOf::CreateI2C CreateI2C(::zx::unowned_channel _client_end, ::fidl::BytePart _request_buffer, ::llcpp::fuchsia::hardware::ftdi::I2cBusLayout layout, ::llcpp::fuchsia::hardware::ftdi::I2cDevice device);

  };

  // Messages are encoded and decoded in-place when these methods are used.
  // Additionally, requests must be already laid-out according to the FIDL wire-format.
  class InPlace final {
    InPlace() = delete;
   public:

    // Create an I2c bus on the FTDI device with a given `layout` and
    // with `device` attached to it.
    static ::fidl::internal::StatusAndError CreateI2C(::zx::unowned_channel _client_end, ::fidl::DecodedMessage<CreateI2CRequest> params);

  };

  // Pure-virtual interface to be implemented by a server.
  class Interface {
   public:
    Interface() = default;
    virtual ~Interface() = default;
    using _Outer = Device;
    using _Base = ::fidl::CompleterBase;

    using CreateI2CCompleter = ::fidl::Completer<>;

    virtual void CreateI2C(::llcpp::fuchsia::hardware::ftdi::I2cBusLayout layout, ::llcpp::fuchsia::hardware::ftdi::I2cDevice device, CreateI2CCompleter::Sync _completer) = 0;

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
    static void CreateI2CRequest(const ::fidl::DecodedMessage<Device::CreateI2CRequest>& _msg);
  };
};

}  // namespace ftdi
}  // namespace hardware
}  // namespace fuchsia
}  // namespace llcpp

namespace fidl {

template <>
struct IsFidlType<::llcpp::fuchsia::hardware::ftdi::I2cDevice> : public std::true_type {};
static_assert(std::is_standard_layout_v<::llcpp::fuchsia::hardware::ftdi::I2cDevice>);
static_assert(offsetof(::llcpp::fuchsia::hardware::ftdi::I2cDevice, address) == 0);
static_assert(offsetof(::llcpp::fuchsia::hardware::ftdi::I2cDevice, vid) == 4);
static_assert(offsetof(::llcpp::fuchsia::hardware::ftdi::I2cDevice, pid) == 8);
static_assert(offsetof(::llcpp::fuchsia::hardware::ftdi::I2cDevice, did) == 12);
static_assert(sizeof(::llcpp::fuchsia::hardware::ftdi::I2cDevice) == ::llcpp::fuchsia::hardware::ftdi::I2cDevice::PrimarySize);

template <>
struct IsFidlType<::llcpp::fuchsia::hardware::ftdi::I2cBusLayout> : public std::true_type {};
static_assert(std::is_standard_layout_v<::llcpp::fuchsia::hardware::ftdi::I2cBusLayout>);
static_assert(offsetof(::llcpp::fuchsia::hardware::ftdi::I2cBusLayout, scl) == 0);
static_assert(offsetof(::llcpp::fuchsia::hardware::ftdi::I2cBusLayout, sda_out) == 4);
static_assert(offsetof(::llcpp::fuchsia::hardware::ftdi::I2cBusLayout, sda_in) == 8);
static_assert(sizeof(::llcpp::fuchsia::hardware::ftdi::I2cBusLayout) == ::llcpp::fuchsia::hardware::ftdi::I2cBusLayout::PrimarySize);

template <>
struct IsFidlType<::llcpp::fuchsia::hardware::ftdi::Device::CreateI2CRequest> : public std::true_type {};
template <>
struct IsFidlMessage<::llcpp::fuchsia::hardware::ftdi::Device::CreateI2CRequest> : public std::true_type {};
static_assert(sizeof(::llcpp::fuchsia::hardware::ftdi::Device::CreateI2CRequest)
    == ::llcpp::fuchsia::hardware::ftdi::Device::CreateI2CRequest::PrimarySize);
static_assert(offsetof(::llcpp::fuchsia::hardware::ftdi::Device::CreateI2CRequest, layout) == 16);
static_assert(offsetof(::llcpp::fuchsia::hardware::ftdi::Device::CreateI2CRequest, device) == 28);

}  // namespace fidl
