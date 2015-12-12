# OSS Sdk for C++, tutorial 4



## Option object
query cors(Cross-origin resource sharing) permissions of a bucket.

```c++
  std::string bucket_name = "<your bucket name>";
  std::string test_key = "test.txt";
  OptionObjectRequest request(bucket_name,
                              test_key,
                              "http://www.google.com",
                              "POST",
                              "a"
                             );
  OptionObjectResult result;
  Status status = client.OptionObject(request, &result);
  if (!status.Ok()) {
    std::cout << "OptionObject failed with " << status.ErrorCode();
    return;
  }
```


## Copy object
copy object from a bucket to another.

```c++
  std::string source_bucket_name = "<your source bucket name>";
  std::string target_bucket_name = "<your target bucket name>";
  std::string source_key = "mysource.txt";
  std::string target_key = "mytarget.txt";
  
  CopyObjectRequest request;
  request.SetSourceBucket(source_bucket_name);
  request.SetSourceKey(source_key);
  request.SetTargetBucket(target_bucket_name);
  request.SetTargetKey(target_key);

  std::unique_ptr<ObjectMetadata> object_metadata(new ObjectMetadata);
  object_metadata->AddHeader("foo", "bar");
  object_metadata->AddHeader("hello", "world");
  object_metadata->AddHeader("highest", "everest");
  request.SetNewObjectMetaData(object_metadata.release());

  CopyObjectResult result;
  Status status = client.CopyObject(request, &result);
  if (!status.Ok()) {
    std::cout << "CopyObject failed with " << status.ErrorCode();
    return;
  }
```
## Get object
download object to local filesystem.

```c++
  std::string bucket_name = "<your bucket name>";
  std::string key = "<your key>";
  std::string down_path = "<your download path>";
  GetObjectRequest request(bucket_name, key, down_path);
  Status status = client.GetObject(request);
  if (!status.Ok()) {
    std::cout << "GetObject failed with " << status.ErrorCode();
    return;
  }
```

## Get object metadata
get metadata of an object.

```c++
  std::string bucket_name = "<your bucket name>";
  std::string key = "<your key>";
  std::unique_ptr<ObjectMetadata> object_metadata;
  Status status = client.GetObjectMetadata(bucket_name,
                                           key,
                                           object_metadata);
  if (!status.Ok()) {
    std::cout << "GetObjectMetadata failed with " << status.ErrorCode();
    return;
  }
```
## Append object
append object.

```c++
  std::string bucket_name = "<your bucket name>";
  std::string append_key = "myappend.txt";
  int64_t file_size = 0;
  std::string file_path = "<your local file path>";
  Status status;

  //phase 1, append from 0.
  {
    AppendObjectRequest request(bucket_name,
                                append_key,
                                file_path,
                                0); //first time file path should be 0;

    status = client.AppendObject(request, NULL);
    if (!status.Ok()) {
      std::cout << "AppendObject failed.\n";
      return;
    }
  }

  //phase 2, get append position.
  {
    std::unique_ptr<ObjectMetadata> object_metadata;
    status = client.GetObjectMetadata(bucket_name,
                             append_key,
                             object_metadata);
    if (!status.Ok()) {
      std::cout << "GetObjectMetadata failed.\n";
      return;
    }
    file_size = object_metadata->GetContentLength();
  }

  //phase 3, append from position.
  {
    AppendObjectRequest request(bucket_name,
                                append_key,
                                file_path,
                                file_size);

    AppendObjectResult result;
    status = client.AppendObject(request, NULL, &result);
    if (!status.Ok()) {
      std::cout << "AppendObject failed.\n";
      return;
    }
  }
```
