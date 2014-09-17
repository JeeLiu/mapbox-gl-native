#ifndef MBGL_STORAGE_BASE_REQUEST
#define MBGL_STORAGE_BASE_REQUEST

#include <mbgl/storage/request_callback.hpp>
#include <mbgl/util/ptr.hpp>

#include <string>
#include <forward_list>
#include <functional>


typedef struct uv_loop_s uv_loop_t;
typedef struct uv_async_s uv_async_t;

namespace mbgl {

class Response;
class Request;

class BaseRequest {
private:
    // Make noncopyable and immovable
    BaseRequest(const BaseRequest &) = delete;
    BaseRequest(BaseRequest &&) = delete;
    BaseRequest& operator=(const BaseRequest &) = delete;
    BaseRequest& operator=(BaseRequest &&) = delete;

public:
    BaseRequest(const std::string &path);
    virtual ~BaseRequest();

    Callback *add(Callback &&callback, const util::ptr<BaseRequest> &request);
    void remove(Callback *callback);
    void notify();

public:
    const unsigned long thread_id;
    const std::string path;
    std::unique_ptr<Response> response;

private:
    // This object may hold a shared_ptr to itself. It does this to prevent destruction of this object
    // while a request is in progress.
    util::ptr<BaseRequest> self;
    std::forward_list<std::unique_ptr<Callback>> callbacks;
};

}

#endif