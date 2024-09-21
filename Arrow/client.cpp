#include <arrow/api.h>
#include <arrow/flight/api.h>
#include <arrow/io/api.h>
#include <arrow/ipc/api.h>
#include <arrow/status.h>
#include <arrow/util/logging.h>

int main() {
    arrow::flight::Location location;
    arrow::Status status = arrow::flight::Location::ForGrpcTcp("localhost", 5005, &location);
    ARROW_CHECK_OK(status);

    std::unique_ptr<arrow::flight::FlightClient> client;
    status = arrow::flight::FlightClient::Connect(location, &client);
    ARROW_CHECK_OK(status);

    arrow::flight::FlightCallOptions options;

    std::unique_ptr<arrow::flight::FlightInfo> flight_info;
    status = client->GetFlightInfo(options, arrow::flight::FlightDescriptor::Path({"example"}), &flight_info);
    ARROW_CHECK_OK(status);

    std::unique_ptr<arrow::flight::FlightStreamReader> stream;
    status = client->DoGet(options, flight_info->endpoints()[0].ticket, &stream);
    ARROW_CHECK_OK(status);

    std::shared_ptr<arrow::RecordBatch> batch;
    while (true) {
        status = stream->Next(&batch);
        if (batch == nullptr || !status.ok()) {
            break;
        }
        ARROW_LOG(INFO) << "Received batch with " << batch->num_rows() << " rows";
    }

    return 0;
}
