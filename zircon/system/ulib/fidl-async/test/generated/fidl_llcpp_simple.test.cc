// WARNING: This file is machine generated by fidlgen.

#include <fidl_llcpp_simple.test.h>
#include <memory>

namespace llcpp {

namespace fidl {
namespace test {
namespace simple {

namespace {

[[maybe_unused]]
constexpr uint64_t kSimple_Echo_Ordinal = 0x7d54c5da00000000lu;
[[maybe_unused]]
constexpr uint64_t kSimple_Echo_GenOrdinal = 0x6a70325976d7cc68lu;
extern "C" const fidl_type_t fidl_test_simple_SimpleEchoRequestTable;
extern "C" const fidl_type_t fidl_test_simple_SimpleEchoResponseTable;
extern "C" const fidl_type_t v1_fidl_test_simple_SimpleEchoResponseTable;
[[maybe_unused]]
constexpr uint64_t kSimple_Close_Ordinal = 0x48270ef100000000lu;
[[maybe_unused]]
constexpr uint64_t kSimple_Close_GenOrdinal = 0x49b6e6b3b17ebc97lu;
extern "C" const fidl_type_t fidl_test_simple_SimpleCloseRequestTable;
extern "C" const fidl_type_t fidl_test_simple_SimpleCloseResponseTable;
extern "C" const fidl_type_t v1_fidl_test_simple_SimpleCloseResponseTable;

}  // namespace
template <>
Simple::ResultOf::Echo_Impl<Simple::EchoResponse>::Echo_Impl(::zx::unowned_channel _client_end, int32_t request) {
  constexpr uint32_t _kWriteAllocSize = ::fidl::internal::ClampedMessageSize<EchoRequest, ::fidl::MessageDirection::kSending>();
  ::fidl::internal::AlignedBuffer<_kWriteAllocSize> _write_bytes_inlined;
  auto& _write_bytes_array = _write_bytes_inlined;
  uint8_t* _write_bytes = _write_bytes_array.view().data();
  memset(_write_bytes, 0, EchoRequest::PrimarySize);
  auto& _request = *reinterpret_cast<EchoRequest*>(_write_bytes);
  _request.request = std::move(request);
  ::fidl::BytePart _request_bytes(_write_bytes, _kWriteAllocSize, sizeof(EchoRequest));
  ::fidl::DecodedMessage<EchoRequest> _decoded_request(std::move(_request_bytes));
  Super::SetResult(
      Simple::InPlace::Echo(std::move(_client_end), std::move(_decoded_request), Super::response_buffer()));
}

Simple::ResultOf::Echo Simple::SyncClient::Echo(int32_t request) {
    return ResultOf::Echo(::zx::unowned_channel(this->channel_), std::move(request));
}

Simple::ResultOf::Echo Simple::Call::Echo(::zx::unowned_channel _client_end, int32_t request) {
  return ResultOf::Echo(std::move(_client_end), std::move(request));
}

template <>
Simple::UnownedResultOf::Echo_Impl<Simple::EchoResponse>::Echo_Impl(::zx::unowned_channel _client_end, ::fidl::BytePart _request_buffer, int32_t request, ::fidl::BytePart _response_buffer) {
  if (_request_buffer.capacity() < EchoRequest::PrimarySize) {
    Super::SetFailure(::fidl::DecodeResult<EchoResponse>(ZX_ERR_BUFFER_TOO_SMALL, ::fidl::internal::kErrorRequestBufferTooSmall));
    return;
  }
  memset(_request_buffer.data(), 0, EchoRequest::PrimarySize);
  auto& _request = *reinterpret_cast<EchoRequest*>(_request_buffer.data());
  _request.request = std::move(request);
  _request_buffer.set_actual(sizeof(EchoRequest));
  ::fidl::DecodedMessage<EchoRequest> _decoded_request(std::move(_request_buffer));
  Super::SetResult(
      Simple::InPlace::Echo(std::move(_client_end), std::move(_decoded_request), std::move(_response_buffer)));
}

Simple::UnownedResultOf::Echo Simple::SyncClient::Echo(::fidl::BytePart _request_buffer, int32_t request, ::fidl::BytePart _response_buffer) {
  return UnownedResultOf::Echo(::zx::unowned_channel(this->channel_), std::move(_request_buffer), std::move(request), std::move(_response_buffer));
}

Simple::UnownedResultOf::Echo Simple::Call::Echo(::zx::unowned_channel _client_end, ::fidl::BytePart _request_buffer, int32_t request, ::fidl::BytePart _response_buffer) {
  return UnownedResultOf::Echo(std::move(_client_end), std::move(_request_buffer), std::move(request), std::move(_response_buffer));
}

::fidl::DecodeResult<Simple::EchoResponse> Simple::InPlace::Echo(::zx::unowned_channel _client_end, ::fidl::DecodedMessage<EchoRequest> params, ::fidl::BytePart response_buffer) {
  Simple::SetTransactionHeaderFor::EchoRequest(params);
  auto _encode_request_result = ::fidl::Encode(std::move(params));
  if (_encode_request_result.status != ZX_OK) {
    return ::fidl::DecodeResult<Simple::EchoResponse>::FromFailure(
        std::move(_encode_request_result));
  }
  auto _call_result = ::fidl::Call<EchoRequest, EchoResponse>(
    std::move(_client_end), std::move(_encode_request_result.message), std::move(response_buffer));
  if (_call_result.status != ZX_OK) {
    return ::fidl::DecodeResult<Simple::EchoResponse>::FromFailure(
        std::move(_call_result));
  }
  return ::fidl::Decode(std::move(_call_result.message));
}

template <>
Simple::ResultOf::Close_Impl<Simple::CloseResponse>::Close_Impl(::zx::unowned_channel _client_end) {
  constexpr uint32_t _kWriteAllocSize = ::fidl::internal::ClampedMessageSize<CloseRequest, ::fidl::MessageDirection::kSending>();
  ::fidl::internal::AlignedBuffer<_kWriteAllocSize> _write_bytes_inlined;
  auto& _write_bytes_array = _write_bytes_inlined;
  uint8_t* _write_bytes = _write_bytes_array.view().data();
  memset(_write_bytes, 0, CloseRequest::PrimarySize);
  ::fidl::BytePart _request_bytes(_write_bytes, _kWriteAllocSize, sizeof(CloseRequest));
  ::fidl::DecodedMessage<CloseRequest> _decoded_request(std::move(_request_bytes));
  Super::SetResult(
      Simple::InPlace::Close(std::move(_client_end), Super::response_buffer()));
}

Simple::ResultOf::Close Simple::SyncClient::Close() {
    return ResultOf::Close(::zx::unowned_channel(this->channel_));
}

Simple::ResultOf::Close Simple::Call::Close(::zx::unowned_channel _client_end) {
  return ResultOf::Close(std::move(_client_end));
}

template <>
Simple::UnownedResultOf::Close_Impl<Simple::CloseResponse>::Close_Impl(::zx::unowned_channel _client_end, ::fidl::BytePart _response_buffer) {
  FIDL_ALIGNDECL uint8_t _write_bytes[sizeof(CloseRequest)] = {};
  ::fidl::BytePart _request_buffer(_write_bytes, sizeof(_write_bytes));
  memset(_request_buffer.data(), 0, CloseRequest::PrimarySize);
  _request_buffer.set_actual(sizeof(CloseRequest));
  ::fidl::DecodedMessage<CloseRequest> _decoded_request(std::move(_request_buffer));
  Super::SetResult(
      Simple::InPlace::Close(std::move(_client_end), std::move(_response_buffer)));
}

Simple::UnownedResultOf::Close Simple::SyncClient::Close(::fidl::BytePart _response_buffer) {
  return UnownedResultOf::Close(::zx::unowned_channel(this->channel_), std::move(_response_buffer));
}

Simple::UnownedResultOf::Close Simple::Call::Close(::zx::unowned_channel _client_end, ::fidl::BytePart _response_buffer) {
  return UnownedResultOf::Close(std::move(_client_end), std::move(_response_buffer));
}

::fidl::DecodeResult<Simple::CloseResponse> Simple::InPlace::Close(::zx::unowned_channel _client_end, ::fidl::BytePart response_buffer) {
  constexpr uint32_t _write_num_bytes = sizeof(CloseRequest);
  ::fidl::internal::AlignedBuffer<_write_num_bytes> _write_bytes;
  ::fidl::BytePart _request_buffer = _write_bytes.view();
  _request_buffer.set_actual(_write_num_bytes);
  ::fidl::DecodedMessage<CloseRequest> params(std::move(_request_buffer));
  Simple::SetTransactionHeaderFor::CloseRequest(params);
  auto _encode_request_result = ::fidl::Encode(std::move(params));
  if (_encode_request_result.status != ZX_OK) {
    return ::fidl::DecodeResult<Simple::CloseResponse>::FromFailure(
        std::move(_encode_request_result));
  }
  auto _call_result = ::fidl::Call<CloseRequest, CloseResponse>(
    std::move(_client_end), std::move(_encode_request_result.message), std::move(response_buffer));
  if (_call_result.status != ZX_OK) {
    return ::fidl::DecodeResult<Simple::CloseResponse>::FromFailure(
        std::move(_call_result));
  }
  return ::fidl::Decode(std::move(_call_result.message));
}


bool Simple::TryDispatch(Interface* impl, fidl_msg_t* msg, ::fidl::Transaction* txn) {
  if (msg->num_bytes < sizeof(fidl_message_header_t)) {
    zx_handle_close_many(msg->handles, msg->num_handles);
    txn->Close(ZX_ERR_INVALID_ARGS);
    return true;
  }
  fidl_message_header_t* hdr = reinterpret_cast<fidl_message_header_t*>(msg->bytes);
  zx_status_t status = fidl_validate_txn_header(hdr);
  if (status != ZX_OK) {
    txn->Close(status);
    return true;
  }
  switch (hdr->ordinal) {
    case kSimple_Echo_Ordinal:
    case kSimple_Echo_GenOrdinal:
    {
      auto result = ::fidl::DecodeAs<EchoRequest>(msg);
      if (result.status != ZX_OK) {
        txn->Close(ZX_ERR_INVALID_ARGS);
        return true;
      }
      auto message = result.message.message();
      impl->Echo(std::move(message->request),
          Interface::EchoCompleter::Sync(txn));
      return true;
    }
    case kSimple_Close_Ordinal:
    case kSimple_Close_GenOrdinal:
    {
      auto result = ::fidl::DecodeAs<CloseRequest>(msg);
      if (result.status != ZX_OK) {
        txn->Close(ZX_ERR_INVALID_ARGS);
        return true;
      }
      impl->Close(
          Interface::CloseCompleter::Sync(txn));
      return true;
    }
    default: {
      return false;
    }
  }
}

bool Simple::Dispatch(Interface* impl, fidl_msg_t* msg, ::fidl::Transaction* txn) {
  bool found = TryDispatch(impl, msg, txn);
  if (!found) {
    zx_handle_close_many(msg->handles, msg->num_handles);
    txn->Close(ZX_ERR_NOT_SUPPORTED);
  }
  return found;
}


void Simple::Interface::EchoCompleterBase::Reply(int32_t reply) {
  constexpr uint32_t _kWriteAllocSize = ::fidl::internal::ClampedMessageSize<EchoResponse, ::fidl::MessageDirection::kSending>();
  FIDL_ALIGNDECL uint8_t _write_bytes[_kWriteAllocSize] = {};
  auto& _response = *reinterpret_cast<EchoResponse*>(_write_bytes);
  Simple::SetTransactionHeaderFor::EchoResponse(
      ::fidl::DecodedMessage<EchoResponse>(
          ::fidl::BytePart(reinterpret_cast<uint8_t*>(&_response),
              EchoResponse::PrimarySize,
              EchoResponse::PrimarySize)));
  _response.reply = std::move(reply);
  ::fidl::BytePart _response_bytes(_write_bytes, _kWriteAllocSize, sizeof(EchoResponse));
  CompleterBase::SendReply(::fidl::DecodedMessage<EchoResponse>(std::move(_response_bytes)));
}

void Simple::Interface::EchoCompleterBase::Reply(::fidl::BytePart _buffer, int32_t reply) {
  if (_buffer.capacity() < EchoResponse::PrimarySize) {
    CompleterBase::Close(ZX_ERR_INTERNAL);
    return;
  }
  auto& _response = *reinterpret_cast<EchoResponse*>(_buffer.data());
  Simple::SetTransactionHeaderFor::EchoResponse(
      ::fidl::DecodedMessage<EchoResponse>(
          ::fidl::BytePart(reinterpret_cast<uint8_t*>(&_response),
              EchoResponse::PrimarySize,
              EchoResponse::PrimarySize)));
  _response.reply = std::move(reply);
  _buffer.set_actual(sizeof(EchoResponse));
  CompleterBase::SendReply(::fidl::DecodedMessage<EchoResponse>(std::move(_buffer)));
}

void Simple::Interface::EchoCompleterBase::Reply(::fidl::DecodedMessage<EchoResponse> params) {
  Simple::SetTransactionHeaderFor::EchoResponse(params);
  CompleterBase::SendReply(std::move(params));
}


void Simple::Interface::CloseCompleterBase::Reply(int32_t v) {
  constexpr uint32_t _kWriteAllocSize = ::fidl::internal::ClampedMessageSize<CloseResponse, ::fidl::MessageDirection::kSending>();
  FIDL_ALIGNDECL uint8_t _write_bytes[_kWriteAllocSize] = {};
  auto& _response = *reinterpret_cast<CloseResponse*>(_write_bytes);
  Simple::SetTransactionHeaderFor::CloseResponse(
      ::fidl::DecodedMessage<CloseResponse>(
          ::fidl::BytePart(reinterpret_cast<uint8_t*>(&_response),
              CloseResponse::PrimarySize,
              CloseResponse::PrimarySize)));
  _response.v = std::move(v);
  ::fidl::BytePart _response_bytes(_write_bytes, _kWriteAllocSize, sizeof(CloseResponse));
  CompleterBase::SendReply(::fidl::DecodedMessage<CloseResponse>(std::move(_response_bytes)));
}

void Simple::Interface::CloseCompleterBase::Reply(::fidl::BytePart _buffer, int32_t v) {
  if (_buffer.capacity() < CloseResponse::PrimarySize) {
    CompleterBase::Close(ZX_ERR_INTERNAL);
    return;
  }
  auto& _response = *reinterpret_cast<CloseResponse*>(_buffer.data());
  Simple::SetTransactionHeaderFor::CloseResponse(
      ::fidl::DecodedMessage<CloseResponse>(
          ::fidl::BytePart(reinterpret_cast<uint8_t*>(&_response),
              CloseResponse::PrimarySize,
              CloseResponse::PrimarySize)));
  _response.v = std::move(v);
  _buffer.set_actual(sizeof(CloseResponse));
  CompleterBase::SendReply(::fidl::DecodedMessage<CloseResponse>(std::move(_buffer)));
}

void Simple::Interface::CloseCompleterBase::Reply(::fidl::DecodedMessage<CloseResponse> params) {
  Simple::SetTransactionHeaderFor::CloseResponse(params);
  CompleterBase::SendReply(std::move(params));
}



void Simple::SetTransactionHeaderFor::EchoRequest(const ::fidl::DecodedMessage<Simple::EchoRequest>& _msg) {
  fidl_init_txn_header(&_msg.message()->_hdr, 0, kSimple_Echo_GenOrdinal);
  _msg.message()->_hdr.flags[0] |= FIDL_TXN_HEADER_UNION_FROM_XUNION_FLAG;
}
void Simple::SetTransactionHeaderFor::EchoResponse(const ::fidl::DecodedMessage<Simple::EchoResponse>& _msg) {
  fidl_init_txn_header(&_msg.message()->_hdr, 0, kSimple_Echo_GenOrdinal);
  _msg.message()->_hdr.flags[0] |= FIDL_TXN_HEADER_UNION_FROM_XUNION_FLAG;
}

void Simple::SetTransactionHeaderFor::CloseRequest(const ::fidl::DecodedMessage<Simple::CloseRequest>& _msg) {
  fidl_init_txn_header(&_msg.message()->_hdr, 0, kSimple_Close_GenOrdinal);
  _msg.message()->_hdr.flags[0] |= FIDL_TXN_HEADER_UNION_FROM_XUNION_FLAG;
}
void Simple::SetTransactionHeaderFor::CloseResponse(const ::fidl::DecodedMessage<Simple::CloseResponse>& _msg) {
  fidl_init_txn_header(&_msg.message()->_hdr, 0, kSimple_Close_GenOrdinal);
  _msg.message()->_hdr.flags[0] |= FIDL_TXN_HEADER_UNION_FROM_XUNION_FLAG;
}

}  // namespace simple
}  // namespace test
}  // namespace fidl
}  // namespace llcpp
