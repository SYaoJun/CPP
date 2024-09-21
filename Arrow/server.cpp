#include <arrow/api.h>
#include <arrow/flight/api.h>
#include <arrow/io/api.h>
#include <arrow/ipc/api.h>
#include <arrow/status.h>
#include <arrow/util/logging.h>

class MyFlightServer : public arrow::flight::FlightServerBase {
public:
    arrow::Status ListFlights(
        const arrow::flight::ServerCallContext&,
        const arrow::flight::Criteria*,
        std::unique_ptr<arrow::flight::FlightListing>* listing) override {
        // 这里你可以列出可用的航班（数据集）
        std::vector<arrow::flight::FlightInfo> flights;
        *listing = std::unique_ptr<arrow::flight::FlightListing>(
            new arrow::flight::SimpleFlightListing(flights));
        return arrow::Status::OK();
    }

    arrow::Status DoGet(
        const arrow::flight::ServerCallContext&,
        const arrow::flight::Ticket& request,
        std::unique_ptr<arrow::flight::FlightDataStream>* data_stream) override {
        // 创建一个简单的表格数据
        std::shared_ptr<arrow::Schema> schema = arrow::schema({
            arrow::field("column1", arrow::int32())
        });

        auto array = std::make_shared<arrow::Int32Array>(arrow::ArrayFromJSON(arrow::int32(), "[1, 2, 3, 4, 5]"));

        auto table = arrow::Table::Make(schema, {array});

        // 创建一个数据流
        auto batch_reader = std::make_shared<arrow::TableBatchReader>(*table);
        *data_stream = std::make_unique<arrow::flight::RecordBatchStream>(batch_reader);

        return arrow::Status::OK();
    }
};

int main() {
    arrow::flight::Location location;
    arrow::Status status = arrow::flight::Location::ForGrpcTcp("localhost", 5005, &location);
    ARROW_CHECK_OK(status);

    arrow::flight::FlightServerOptions options(location);

    MyFlightServer server;
    status = server.Init(options);
    ARROW_CHECK_OK(status);

    ARROW_LOG(INFO) << "Server is listening on localhost:5005";
    status = server.Serve();
    ARROW_CHECK_OK(status);

    return 0;
}
