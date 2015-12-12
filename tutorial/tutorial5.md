# OSS Sdk for C++, tutorial 5



## Multiple upload(local)
upload local file by spliting file into several parts.

```c++
  Status status;
  std::string bucket_name = "<your bucket name>";
  const std::string key = "niu.c";
  std::string file_path = "<your file path>";
  //first, we have to applying an upload id.
  std::string upload_id;
  {
    InitiateMultipartUploadRequest request(bucket_name, key);
    InitiateMultipartUploadResult result;
    status = client.InitiateMultipartUpload(request, &result);
    if (!status.Ok()) {
      std::cout << "InitiateMultipartUpload failed\n";
      return;
    }
    upload_id = result.GetUploadId();
  }

  //then, we query local file size.
  int64_t file_size = GetFileSize(file_path);
  if (file_size == -1) {
    std::cout << "GetFileSize failed\n";
    return;
  }

  //then spite file into several files and upload.
  std::list<PartEtag> part_etags;
  int64_t part_size = 100 * 1024;
  auto part_count = (file_size + part_size - 1) / part_size;
  std::vector<std::unique_ptr<std::ifstream>> streams;
  for (auto i = 0; i < part_count; ++i) {
    streams.push_back(
      std::move(std::unique_ptr<std::ifstream>(new std::ifstream)));
    std::ifstream& stream = *streams[i];
    stream.open(file_path, std::ios::in | std::ios::binary);
    if (!stream) {
      std::cout << "open stream failed\n";
      return;
    }

    streams[i]->seekg(part_size * i, std::ios::beg);
    int64_t actual_size = (i + 1 != part_count) ?
                          part_size : (file_size - part_size * i);

    std::string md5_digest =
      AprBase64Encode(AprComputeFileMd5(&stream, actual_size));

    UploadPartRequest request{
      bucket_name,
      key,
      upload_id,
      &stream,
      i + 1,
      actual_size,
      md5_digest
    };

    UploadPartResult result;
    //do upload file.
    status = client.UploadPart(request, &result);
    if (!status.Ok()) {
      std::cout << "UploadPart failed\n";
      return;
    }
    part_etags.push_back(PartEtag(result.GetEtag(), i + 1));
  }

  //finally we complete by upload id
  {
    CompleteMultipartUploadrequest request(bucket_name, key, upload_id);
    CompleteMultipartUploadResult result;
    request.MutableEtagList().swap(part_etags);
    status = client.CompleteMultipartUpload(request, &result);
    if (!status.Ok()) {
      std::cout << "CompleteMultipartUpload failed\n";
      return;
    }
  }
```


## Multiple upload(remote)
upload remote file by spliting file into several parts.

```c++
  Status status;
  std::string source_bucket_name = "<your bucket name>";
  std::string target_bucket_name = "<your file path>";
  std::string source_key = "mysource1.txt";
  std::string target_key = "mytarget1.txt";

  int64_t part_size = 100 * 1024;
  int64_t file_size = 0;
  //first, get remote source object size.
  {
    std::unique_ptr<ObjectMetadata> object_metadata;
    client.GetObjectMetadata(
      source_bucket_name,
      source_key,
      object_metadata
    );
    file_size = object_metadata->GetContentLength();
  }

  //then get an upload id.
  std::string upload_id;
  {
    InitiateMultipartUploadRequest request(target_bucket_name, target_key);
    InitiateMultipartUploadResult result;
    status = client.InitiateMultipartUpload(request, &result);
    if (!status.Ok()) {
      std::cout << "InitiateMultipartUpload failed\n";
      return;
    }
    upload_id = result.GetUploadId();
  }

  //split and upload.
  std::list<PartEtag> part_etags;
  auto part_count = (file_size + part_size - 1) / part_size;
  for (auto i = 0; i < part_count; ++i) {
    int64_t actual_size = (i + 1 != part_count) ?
                          part_size : (file_size - part_size * i);

    UploadPartCopyRequest request{
      source_bucket_name_,
      source_key,
      target_bucket_name_,
      target_key,
      upload_id,
      i + 1,
      actual_size,
      i * part_size
    };

    UploadPartCopyResult result;
    //do copy
    status = client.UploadPartCopy(request, &result);
    part_etags.push_back(PartEtag(result.GetEtag(), i + 1));
    if (!status.Ok()) {
      std::cout << "UploadPartCopy failed\n";
      return;
    }
  }

  {
    CompleteMultipartUploadrequest request(target_bucket_name,
                                           target_key,
                                           upload_id);
    CompleteMultipartUploadResult result;
    request.MutableEtagList().swap(part_etags);
    //complete task.
    status = client.CompleteMultipartUpload(request, &result);
    if (!status.Ok()) {
      std::cout << "CompleteMultipartUpload failed\n";
      return;
    }
  }
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

## Upload parts management
demostrate how to list and abort parts..

```c++
  Status status;
  std::string bucket_name = "<your bucket name>";

  for (int i = 0; i < 5; ++i) {
    InitiateMultipartUploadRequest request(bucket_name, "temp_part");
    InitiateMultipartUploadResult result;
    status = client.InitiateMultipartUpload(request, &result);
    if (!status.Ok()) {
      std::cout << "InitiateMultipartUpload failed" << std::endl;
      return;
    }
  }

  ListMultipartUploadsRequest request;
  request.SetBucketName(bucket_name);
  request.SetMaxUploads(1000);
  ListMultipartUploadsResult result;
  status = client.ListMultipartUploads(request, &result);
  if (!status.Ok()) {
    std::cout << "ListMultipartUploads failed" << std::endl;
    return;
  }
  for (auto& upload : result.GetMultipartUpload()) {
    status = client.AbortMultipartUpload(bucket_name_,
                                upload.GetKey(),
                                upload.GetUploadId());
    if (!status.Ok()) {
      std::cout << "AbortMultipartUpload failed" << std::endl;
      return;
    }
  }
  std::cout << "ListMultipartUploads succeed" << std::endl;
```
