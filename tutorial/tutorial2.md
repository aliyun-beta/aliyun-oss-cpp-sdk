# OSS Sdk for C++, tutorial 2



## Set bucket logging
set logging configuration to a bucket. 

```c++
  std::string bucket_name = "<your bucket name>";
  std::string targe_bucket_name = "<target bucket name>";
  std::string prefix = "<your prefix>";
  SetBucketLoggingRequest request(targe_bucket_name, prefix, bucket_name);
  Status status = client_.SetBucketLogging(request);
  if (!status.Ok()) {
    std::cout << "BucketExists failed with " << status.ErrorCode();
    return;
  }
```


## Get bucket logging
get logging configuration fo a bucket.

```c++
  std::string bucket_name = "<your bucket name>";
  GetBucketLoggingResult result;
  Status status = client_.GetBucketLogging(bucket_name, &result);
  if (!status.Ok()) {
    std::cout << "GetBucketLogging failed with " << status.ErrorCode();
    return;
  }
```

## Delete bucket logging
delete logging configuration to a bucket.

```c++
  std::string bucket_name = "<your bucket name>";
  GetBucketLoggingResult result;
  Status status = client_.DeleteBucketLogging(bucket_name);
  if (!status.Ok()) {
    std::cout << "DeleteBucketLogging failed with " << status.ErrorCode();
    return;
  }
```

## Get bucket website
get website configuration of a bucket.

```c++
  std::string index_page = "index.html";
  std::string not_found_page = "404.html";
  SetBucketWebsiteRequest request(bucket_name_, index_page, not_found_page);
  Status status = client_.SetBucketWebsite(request);
  if (!status.Ok()) {
    std::cout << "SetBucketWebsite failed with " << status.ErrorCode();
    return;
  }
```

## Delete bucket website
delete website configuration of an bucket

```c++
  std::string bucket_name = "<your bucket name>";
  GetBucketWebsiteResult result;
  Status status = client_.GetBucketWebsite(bucket_name, &result);
  if (!status.Ok()) {
    std::cout << "GetBucketWebsite failed with " << status.ErrorCode();
    return;
  }
```

## Set bucket referer
set referer configuration to bucket.

```c++
  std::string bucket_name = "<your bucket name>";
  SetBucketRefererRequest request(bucket_name);
  request.AddReferer("http://www.yahoo.com");
  request.AddReferer("http://www.microsoft.com");
  request.AddReferer("http://www.msn.com");
  request.AddReferer("http://www.aliyun.com");
  request.AddReferer("http://www.*.com");
  request.AddReferer("http://www.?.aliyuncs.com");

  request.SetAllowEmpty(false);

  Status status = client_.SetBucketReferer(request);
  if (!status.Ok()) {
    std::cout << "SetBucketReferer failed with " << status.ErrorCode();
    return;
  }
```
note that there is no DeleteBucketReferer api, but you can specify an empty referer list by SetBucketReferer.

## Get bucket referer
get referer configuration of a bucket.

```c++
  std::string bucket_name = "<your bucket name>";
  GetBucketRefererResult result;
  Status status = client_.GetBucketReferer(bucket_name, &result);
  if (!status.Ok()) {
    std::cout << "SetBucketReferer failed with " << status.ErrorCode();
    return;
  }
```

## Set bucket cors
set cors configuration to a bucket.

```c++
  std::string bucket_name = "<your bucket name>";
  SetBucketCorsRequest request(bucket_name_);

  CorsRule rule1;
  rule1.AddAllowedOrigin("http://www.a.com");
  rule1.AddAllowedMethod("POST");
  rule1.AddAllowedHeader("*");
  rule1.AddExposeHeader("x-oss-test");
  rule1.SetMaxAgeSeconds(300);
  request.AddRule(rule1);

  CorsRule rule2;
  rule2.AddAllowedOrigin("http://www.google.com");
  rule2.AddAllowedOrigin("http://www.facebook.com");
  rule2.AddAllowedOrigin("http://www.aliyun.com");
  rule2.AddAllowedMethod("POST");
  rule2.AddAllowedMethod("GET");
  rule2.AddAllowedHeader("a");
  rule2.AddAllowedHeader("b");
  rule2.AddAllowedHeader("c");
  rule2.AddExposeHeader("x-oss-test1");
  rule2.AddExposeHeader("x-oss-test2");
  rule2.SetMaxAgeSeconds(200);
  request.AddRule(rule2);

  Status status = client_.SetBucketCors(request);
  if (!status.Ok()) {
    std::cout << "SetBucketReferer failed with " << status.ErrorCode();
    return;
  }
```
## Get bucket cors
get cors configuration of a bucket.

```c++
  std::string bucket_name = "<your bucket name>";
  GetBucketCorsResult result;
  Status status = client_.GetBucketCors(bucket_name, &result);
  if (!status.Ok()) {
    std::cout << "SetBucketReferer failed with " << status.ErrorCode();
    return;
  }
```

## Delete bucket cors
delete cors configuration of a bucket.

```c++
  std::string bucket_name = "<your bucket name>";
  Status status = client_.DeleteBucketCors(bucket_name);
  if (!status.Ok()) {
    std::cout << "SetBucketReferer failed with " << status.ErrorCode();
    return;
  }
```
