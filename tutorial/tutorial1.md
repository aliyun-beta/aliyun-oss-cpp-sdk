# OSS Sdk for C++, tutorial  1



## OSSClient
First step, you need to create an OSSClient instance.

```c++
  #include "oss_sdk/oss/oss_client.h"
  using namespace oss;

  std::string endpoint = "oss-cn-hangzhou.aliyuncs.com";
  std::string access_key_id = "<your access id>";
  std::string access_key_secret = "<your access key>";

  OssClient client(endpoint, access_key_id, access_key_secret);
```


## List buckets
list all buckets.

```c++
  std::vector<Bucket> buckets;
  Status status = client_.ListBuckets(&buckets);
  if (!status.Ok()) {
    std::cout << "ListBuckets failed." << std::endl;
    return;
  }
  for (auto& bucket : buckets) {
    std::cout << bucket.GetName() << ", " << bucket.GetLocation()
              << ", " << bucket.GetCreationDate() << std::endl;
  }
  std::cout << std::endl;
```

also you can specify parameters to do conditional query.

```c++
  ListBucketsRequest request;
  request.SetMaxKeys(2); //limit max result count.
  request.SetPrefix("m"); //limit prefix.

  ListBucketsResult result;
  Status status = client_.ListBuckets(request, &result);
  if (!status.Ok()) {
    std::cout << "ListBuckets failed." << std::endl;
    return;
  }
  for (auto& bucket : result.GetBuckets()) {
    std::cout << bucket.GetName() << ", " << bucket.GetLocation()
              << ", " << bucket.GetCreationDate() << std::endl;
  }
```

## Create bucket
create bucket.

```c++
  std::string bucket_name = "<your bucket name>";
  Status status = client_.CreateBucket(bucket_name, kAclPrivate);
  if (!status.Ok()) {
    std::cout << "CreateBucket failed." << std::endl;
  }
```
the second argument can be kAclPrivate, kAclPublicReadWrite, kAclPublicRead.

## Delete bucket
delete bucket.

```c++
  std::string bucket_name = "<your bucket name>";
  Status status = client_.DeleteBucket(bucket_name);
  if (!status.Ok()) {
    std::cout << "CreateBucket failed with " << status.ErrorCode();
  }
```
if the bucket does not exist, can error code should be kNoSuchBucket.

## Bucket existance
Determine existance of a bucket.

```c++
  bool exist = false;
  Status status = client_.BucketExists(bucket_name_, &exist);
  if (!status.Ok()) {
    std::cout << "BucketExists failed with " << status.ErrorCode();
  }
```

## Bucket location
####Get datacenter of a bucket, the return value should be one of these:
* oss-cn-hangzhou
* oss-cn-qingdao
* oss-cn-beijing
* oss-cn-hongkong
* oss-cnshenzhen
* oss-cn-shanghai
* oss-us-west-1
* oss-ap-southeast-1

```c++
  std::string bucket_name = "<your bucket name>";
  std::string location;
  Status status = client_.GetBucketLocation(bucket_name, &location);
  if (!status.Ok()) {
    std::cout << "BucketExists failed with " << status.ErrorCode();
    return;
  }
  std::cout << "Location of bucket " << bucket_name << " is " << location;
}
```