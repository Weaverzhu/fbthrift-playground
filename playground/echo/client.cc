#include "playground/idl/gen-cpp2/EchoServiceAsyncClient.h"
#include <folly/executors/CPUThreadPoolExecutor.h>
#include <folly/init/Init.h>
#include <glog/logging.h>
#include <thrift/lib/cpp2/async/HeaderClientChannel.h>
#include <thrift/lib/cpp2/server/ThriftProcessor.h>
#include <thrift/lib/cpp2/server/ThriftServer.h>

using idl::echo::EchoRequest;
using idl::echo::EchoResponse;

using apache::thrift::ThriftServer;
using apache::thrift::ThriftServerAsyncProcessorFactory;
int main(int argc, char *argv[]) {
  folly::init(&argc, &argv);

  folly::EventBase evb;
  std::unique_ptr<folly::AsyncSocket, folly::DelayedDestruction::Destructor>
      socket(new folly::AsyncSocket(&evb,
                                    folly::SocketAddress("127.0.0.1", 12345)));

  auto channel =
      apache::thrift::HeaderClientChannel::newChannel(std::move(socket));
  auto client =
      std::make_shared<idl::echo::EchoServiceAsyncClient>(std::move(channel));
  apache::thrift::RpcOptions options;
  EchoRequest req;
  req.message_ref() = "hello";
  EchoResponse rsp;

  try {
    client->sync_echo(rsp, req);
    LOG(INFO) << "[echo client]" << rsp.get_message();
    client->sync_oneway_echo(req);
    client->sync_echo(rsp, req);
    LOG(INFO) << "[echo client]" << rsp.get_message();

  } catch (std::exception &e) {
    LOG(ERROR) << "exception " << e.what();
  }
  return 0;
}