# OSS Sdk for C++, tutorial 3



## List objects
list objects in a bucket.

```c++
  std::string bucket_name = "<your bucket name>";
  ListObjectsRequest request;
  request.SetBucketName(bucket_name_);
  request.SetMaxKeys(100); //limit max return count.

  ListObjectsResult result;
  Status status = client_.ListObjects(request, &result);
  if (!status.Ok()) {
    std::cout << "ListObjects failed with " << status.ErrorCode();
    return;
  }
  for (auto& content : result.GetContents()) {
    std::cout << content.GetKey() << std::endl;
  }
```


## Create folder
create a pure folder.

```c++
  const std::string folder_name = "testfolder1";
  std::string bucket_name = "<your bucket name>";
  Status status = client.CreateFolder(bucket_name, folder_name);
  if (!status.Ok()) {
    std::cout << "CreateFolder failed with " << status.ErrorCode();
    return;
  }
```

## Object existance
test object existance.

```c++
  std::string bucket_name = "<your bucket name>";
  std::string key = "hello.txt";
  bool exist;
  Status status = client_.ObjectExists(bucket_name_, key, &exist);
  if (!status.Ok()) {
    std::cout << "ObjectExists failed with " << status.ErrorCode();
    return;
  }
```

## Put object
create an object from local file.

```c++
  std::string bucket_name = "<your bucket name>";
  std::string test_key = "test.txt";
  std::string file_path = "/root/test/abc.txt";
  Status status = client_.PutObject(bucket_name, test_key, file_path);
  if (!status.Ok()) {
    std::cout << "DeleteObject failed with " << status.ErrorCode();
    return;
  }
```
you can also do it from an opened stream.

```c++
  std::string bucket_name = "<your bucket name>";
  std::string file_path = "/home/allen/test/test.txt";
  std::string test_key =  "test.txt";
  std::ifstream stream(file_path);
  if (!stream) {
    std::cout << "OpenStream failed!" << std::endl;
    return;
  }
  Status status = client.PutObject(bucket_name, test_key, &stream);
  if (!status.Ok()) {
    std::cout << "PutObject failed with " << status.ErrorCode();
    return;
  }
```
if you wanna use custom header like Content-MD5 etc, you can do it like this:

```c++
  std::string bucket_name = "<your bucket name>";
  std::string file_path = "/home/allen/test/test.txt";
  std::string test_key =  "test.txt";
  std::ifstream stream(file_path);
  if (!stream) {
    std::cout << "OpenStream failed!" << std::endl;
    return;
  }

  std::unique_ptr<ObjectMetadata> object_metadata(new ObjectMetadata);
  object_metadata->AddHeader("Content-Type", "text/plain");
  //Compute file MD5 and encode it to base64.
  std::string content_md5 = AprBase64Encode(AprComputeFileMd5(stream));
  object_metadata->AddHeader("Content-MD5", content_md5);

  Status status = client.PutObject(bucket_name,
                                    test_key,
                                    &stream,
                                    object_metadata.get());
  if (!status.Ok()) {
    std::cout << "PutObject failed with " << status.ErrorCode();
    return;
  }
```
## Delete object
delete an object 

```c++
  std::string bucket_name = "<your bucket name>";
  std::string test_key = "test.txt";
  Status status = client.DeleteObject(bucket_name, test_key);
  if (!status.Ok()) {
    std::cout << "DeleteObject failed with " << status.ErrorCode();
    return;
  }
```
## Delete multiple objects
delete multiple objects

```c++
  std::string bucket_name = "<your bucket name>";
  std::list<std::string> keys = { "foo.txt", "bar.txt"};
  DeleteMultipleObjectsRequest request(bucket_name, keys);
  DeleteMultipleObjectsResult result;
  Status status = client.DeleteMultipleObjects(request, &result);
  if (!status.Ok()) {
    std::cout << "DeleteMultipleObjects failed with " << status.ErrorCode();
    return;
  }
```
