#include "playground/idl/gen-cpp2/EchoService.h"
#include <folly/init/Init.h>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <thrift/lib/cpp2/server/ThriftProcessor.h>
#include <thrift/lib/cpp2/server/ThriftServer.h>

using idl::echo::EchoRequest;
using idl::echo::EchoResponse;

DEFINE_int32(port, 12345, "");

class EchoServiceInterface : public idl::echo::EchoServiceSvIf {
public:
  virtual void echo(EchoResponse &rsp, std::unique_ptr<EchoRequest> req) {
    LOG(INFO) << "[echo server] echo " << req->get_message();
    rsp.message_ref() = req->get_message();
  }

  virtual void oneway_echo(std::unique_ptr<::idl::echo::EchoRequest> req) {
    LOG(INFO) << "[echo server] oneway echo " << req->get_message();
  }
};

using apache::thrift::ThriftServer;
using apache::thrift::ThriftServerAsyncProcessorFactory;
int main(int argc, char *argv[]) {
  folly::init(&argc, &argv);

  auto handler = std::make_shared<EchoServiceInterface>();
  auto proc_factory = std::make_shared<
      apache::thrift::ThriftServerAsyncProcessorFactory<EchoServiceInterface>>(
      handler);

  auto server = std::make_shared<ThriftServer>();
  server->setMaxResponseSize(1 << 20);
  server->setPort(FLAGS_port);
  server->setInterface(std::make_shared<EchoServiceInterface>());
  try {
    server->serve();
  } catch (std::exception &e) {
    printf("[server exception] %s\n", e.what());
  }

  return 0;
}