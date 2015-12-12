# OSS C++ SDK

# License
Apache License 2.0
    
# System requirements
  + Ubuntu 12.04 tested, gcc 4.6
  + Windows 7+, Visual Studio 2013 update4+
  + Mac OSX 10.10, LLVM 7.0.0 tested.

# How to build
  + Windows
    + open all.sln in visual studio and build.
  + Linux(ubuntu 12.04)
    + 1, install cmake, run sudo apt-get install cmake
    + 2, install dependencies, run sudo apt-get install libapr1-dev libaprutil1-dev libtinyxml-dev libcurl4-openssl-dev
    + 3, run cmake .&& make
  + Mac OSX
    + 1, install cmake, run sudo brew install cmake
    + 2, install dependencies, run brew install tinyxml apr apr-util curl
    + 3, then run cmake .&& make

# Api Index

* [Bucket](#listbuckets)
  + [ListBuckets](#listbuckets)
  + [CreateBucket](#createbucket)
  + [DeleteBucket](#deletebucket)
  + [BucketExists](#bucketexists)
  + [SetBucketAcl](#setbucketacl)
  + [GetBucketAcl](#getbucketacl)
  + [GetBucketLocation](#getbucketlocation)
  + [GetBucketLogging](#getbucketlogging)
  + [SetBucketLogging](#setbucketlogging)
  + [DeleteBucketLogging](#deletebucketlogging)
  + [GetBucketWebsite](#getbucketwebsite)
  + [SetBucketWebsite](#setbucketwebsite)
  + [DeleteBucketWebsite](#deletebucketwebsite)
  + [GetBucketReferer](#getbucketreferer)
  + [SetBucketReferer](#setbucketreferer)
  + [GetBucketLifecycle](#getbucketlifecycle)
  + [SetBucketLifecycle](#setbucketlifecycle)
  + [DeleteBucketLifecycle](#deletebucketlifecycle)
  + [GetBucketCors](#getbucketcors)
  + [SetBucketCors](#setbucketcors)
  + [DeleteBucketCors](#deletebucketcors)
* [Object](#listobjects)
  + [ListObjects](#listobjects)
  + [CreateFolder](#createfolder)
  + [ObjectExists](#objectexists)
  + [PutString](#putobject)
  + [PutObject](#putobject)
  + [DeleteObject](#deleteobject)
  + [DeleteMultipleObjects](#deletemultipleobjects)
  + [OptionObject](#optionobject)
  + [CopyObject](#copyobject)
  + [GetObject](#getobject)
  + [GetObjectMetadata](#getobjectmetadata)
  + [AppendObject](#appendobject)
  + [InitiateMultipartUpload](#initiatemultipartupload)
  + [UploadPart](#uploadpart)
  + [UploadPartCopy](#uploadpartcopy)
  + [CompleteMultipartUpload](#completemultipartupload)
  + [AbortMultipartUpload](#abortmultipartupload)
  + [ListMultipartUploads](#listmultipartuploads)
  + [ListParts](#listparts)



## ListBuckets
```c++
  Status ListBuckets(const ListBucketsRequest& request, ListBucketsResult* result);
  Status ListBuckets(std::vector<Bucket>* buckets);
```
#### Request Parameters
  * prefix — return buckets must begin with prefix
  * marker — return buckets must start from marker.
  * max-key — return buckets must no more than max-keys.

------------------------------------------------------------------------------

## CreateBucket
```c++
Status CreateBucket(const std::string& bucket_name, const std::string& acl = kAclPrivate);
```
#### Request Parameters
  * bucket_name — the bucket name you wanna use
  * acl — initial acl, default to "private"

------------------------------------------------------------------------------

## DeleteBucket
```c++
  Status DeleteBucket(const std::string& bucket_name);
```
#### Request Parameters
  * bucket_name — bucket name

------------------------------------------------------------------------------

## BucketExists
```c++
  Status BucketExists(const std::string& bucket_name, bool* exist);
```
#### Request Parameters
  * bucket_name — bucket name


------------------------------------------------------------------------------

## SetBucketAcl
```c++
  Status SetBucketAcl(const std::string& bucket_name,
                      const std::string& acl = kAclPrivate);
```
#### Request Parameters
  * bucket_name — bucket name
  * acl — access permission you want to set.


------------------------------------------------------------------------------

## GetBucketAcl
```c++
  Status GetBucketAcl(const std::string& bucket_name, std::string* acl);
```
#### Request Parameters
  * bucket_name — bucket name


------------------------------------------------------------------------------

## GetBucketLocation
```c++
 Status GetBucketLocation(const std::string& bucket_name, std::string* location);
```
#### Request Parameters
  * bucket_name — bucket name


------------------------------------------------------------------------------

## GetBucketLogging
```c++
  Status GetBucketLogging(const std::string& bucket_name, GetBucketLoggingResult* result);
```
#### Request Parameters
  * bucket_name — bucket name

------------------------------------------------------------------------------

## SetBucketLogging
```c++
  Status SetBucketLogging(const SetBucketLoggingRequest& request);
```
#### Request Parameters
  * target_bucket —  the bucket actually store logs.
  * target_prefix —  the prefix of log file name.
  * source_bucket —  the bucket you want to enable logging on.

------------------------------------------------------------------------------

## DeleteBucketLogging
```c++
  Status DeleteBucketLogging(const std::string& bucket_name); 
```
#### Request Parameters
  * bucket_name — bucket name


------------------------------------------------------------------------------

## GetBucketWebsite
```c++
  Status GetBucketWebsite(const std::string& bucket_name, GetBucketWebsiteResult* result);
```
#### Request Parameters
  * bucket_name — bucket name


------------------------------------------------------------------------------

## SetBucketWebsite
```c++
  Status SetBucketWebsite(const std::string& bucket_name,
                          const std::string& index_page,
                          const std::string& error_page); 
```
#### Request Parameters
  * bucket_name — bucket name
  * index_page — bucket's index page.
  * error_page — bucket's "not found" page


------------------------------------------------------------------------------

## DeleteBucketWebsite
```c++
  Status DeleteBucketWebsite(const std::string& bucket_name);
```
#### Request Parameters
  * bucket_name — bucket name


------------------------------------------------------------------------------

## GetBucketReferer
```c++
  Status GetBucketReferer(const std::string& bucket_name,
                          GetBucketRefererResult* result);
```
#### Request Parameters
  * bucket_name — bucket name


------------------------------------------------------------------------------

## SetBucketReferer
```c++
  Status SetBucketReferer(const SetBucketRefererRequest& request);
```
#### Request Parameters
  * bucket_name — bucket name
  * referer_list — allow website list.
  * allow_empty — allow empty refere or not.

------------------------------------------------------------------------------
## GetBucketLifecycle
```c++
  Status GetBucketLifecycle(const std::string& bucket_name,
                            GetBucketLifecycleResult* result);
```
#### Request Parameters
  * bucket_name — bucket name

------------------------------------------------------------------------------

------------------------------------------------------------------------------
## SetBucketLifecycle
```c++
  Status GetBucketLifecycle(const std::string& bucket_name,
                            GetBucketLifecycleResult* result);
```
#### Request Parameters
  * bucket_name — bucket name
  * rule_list — lifecycle rule list

------------------------------------------------------------------------------

## DeleteBucketLifecycle
```c++
  Status DeleteBucketLifecycle(const std::string& bucket_name);
```
#### Request Parameters
  * bucket_name — bucket name


------------------------------------------------------------------------------

## GetBucketCors
```c++
  Status GetBucketCors(const std::string& bucket_name,
                       GetBucketCorsResult* result);
```
#### Request Parameters
  * bucket_name — bucket name

------------------------------------------------------------------------------

## SetBucketCors
```c++
  Status SetBucketCors(const SetBucketCorsRequest& request);
```
#### Request Parameters
  * bucket_name — bucket name
  * rule_list — cors rule list


------------------------------------------------------------------------------

## DeleteBucketCors
```c++
  Status DeleteBucketCors(const std::string& bucket_name);
```
#### Request Parameters
  * bucket_name — bucket name


------------------------------------------------------------------------------

## ListObjects
```c++
  Status ListObjects(const ListObjectsRequest& request, ListObjectsResult* result);
```
#### Request Parameters
  * bucket_name — bucket name
  * delimiter — delimiter used to group objects
  * prefix — return objects must begin with prefix
  * marker — return objects must start from marker.
  * max-key — return objects must no more than max-keys.


------------------------------------------------------------------------------

## CreateFolder
```c++
 Status CreateFolder(const std::string& bucket_name, const std::string& folder_name);
```
#### Request Parameters
  * bucket_name — bucket name
  * folder_name — folder name, no matter with or without slash(/)

------------------------------------------------------------------------------

## ObjectExists
```c++
Status ObjectExists(const std::string& bucket_name, const std::string& key, bool* exist);
```
#### Request Parameters
  * bucket_name — bucket name
  * key — object key

------------------------------------------------------------------------------

## PutString
```c++
  Status PutString(const std::string & bucket_name,
                   const std::string & key,
                   const std::string & str,
                   const ObjectMetadata* object_metadata = NULL);
```
#### Request Parameters
  * bucket_name — bucket name
  * key — object key
  * str — arbitrary data used to write to the object
  * object_metadata — specify your own object metadata

------------------------------------------------------------------------------

## PutObject
```c++
  Status PutObject(const std::string & bucket_name,
                   const std::string & key,
                   const std::string & file_path,
                   const ObjectMetadata* object_metadata = NULL);

  Status PutObject(const std::string& bucket_name,
                   const std::string& key,
                   const std::string& file_path,
                   int64_t stream_bytes,
                   const ObjectMetadata* object_metadata = NULL);


  Status PutObject(const std::string& bucket_name,
                   const std::string& key,
                   std::ifstream* stream,
                   const ObjectMetadata* object_metadata = NULL);

  Status PutObject(const std::string& bucket_name,
                   const std::string& key,
                   std::ifstream* stream,
                   int64_t stream_bytes,
                   const ObjectMetadata* object_metadata = NULL);
```
#### Request Parameters
  * bucket_name — bucket name
  * key — object key
  * file_path — local file to upload
  * stream — local stream to upload
  * stream_bytes — upload bytes must no more than stream_bytes.
  * object_metadata — specify your own object metadata.


------------------------------------------------------------------------------

## DeleteObject
```c++
  Status DeleteObject(const std::string & bucket_name,  const std::string & key);
```
#### Request Parameters
  * bucket_name — bucket name


------------------------------------------------------------------------------

## DeleteMultipleObjects
```c++
  Status DeleteMultipleObjects(const DeleteMultipleObjectsRequest& request,
                               DeleteMultipleObjectsResult* result);
```
#### Request Parameters
  * bucket_name — bucket name
  * key — object key
  * quiet — if true, result contains all the key in your request
    otherwise, result only contains "failed deletion" keys.

------------------------------------------------------------------------------

## OptionObject
```c++
 Status OptionObject(const OptionObjectRequest& request, OptionObjectResult* result);
```
#### Request Parameters
  * bucket_name — bucket name
  * key — object key
  * origin — origin used to test
  * request_method — http method used to test
  * request_headers — http header used to test.


------------------------------------------------------------------------------

## CopyObject
```c++
  Status CopyObject(const CopyObjectRequest& request, CopyObjectResult* result);
```
#### Request Parameters
  * source_bucket — source bucket
  * source_key — source key
  * target_bucket — target bucket
  * target_key — target key
  * ...
  * ...

------------------------------------------------------------------------------

## GetObject
```c++
  Status GetObject(const GetObjectRequest& request);
```
#### Request Parameters
  * bucket_name — bucket name
  * key — object key
  * file_path — download to this path
  * output_stream — download to this stream

------------------------------------------------------------------------------

## GetObjectMetadata
```c++
  Status GetObjectMetadata(const std::string& bucket_name,
                           const std::string& key,
                           std::unique_ptr<ObjectMetadata>* object_meta_data);
 
```
#### Request Parameters
  * bucket_name — bucket name
  * key — object key

------------------------------------------------------------------------------

## AppendObject
```c++
  Status AppendObject(const AppendObjectRequest& request);

  Status AppendObject(const AppendObjectRequest& request,
                      const ObjectMetadata* object_metadata);

  Status AppendObject(const AppendObjectRequest& request,
                      const ObjectMetadata* object_metadata,
                      AppendObjectResult* result);
```
#### Request Parameters
  * bucket_name — bucket name
  * key — object key
  * file_path — local file for upload
  * position — position of file for read from.

------------------------------------------------------------------------------

## InitiateMultipartUpload
```c++
  Status InitiateMultipartUpload(const InitiateMultipartUploadRequest& request,
                                 InitiateMultipartUploadResult* result);
```
#### Request Parameters
  * bucket_name — bucket name
  * key — object key


------------------------------------------------------------------------------

## UploadPart
```c++
  Status UploadPart(const UploadPartRequest& request, UploadPartResult* result);
```
#### Request Parameters
  * bucket_name — bucket name
  * key — object key
  * upload_id — unique id for upload
  * input_steam — stream for read
  * part_number — part unique number.
  * part_size — bytes to read
  * md5_digest — md5 checksum for chcksum.


------------------------------------------------------------------------------

## UploadPartCopy
```c++
  Status UploadPartCopy(const UploadPartCopyRequest& request,
                        UploadPartCopyResult* result);
```
#### Request Parameters
  * source_bucket — souree bucket name
  * source_key — souree object key
  * target_bucket — target bucket name
  * target_key — target object key
  * upload_id — unique id for upload
  * part_number — part unique number.
  * part_size — bytes to read

------------------------------------------------------------------------------

## CompleteMultipartUpload
```c++
  Status CompleteMultipartUpload(const CompleteMultipartUploadrequest& request,
                                 CompleteMultipartUploadResult* result);
```
#### Request Parameters
  * bucket_name — bucket name
  * key — object key
  * upload_id — unique id for upload
  * etag_list — etag list of previous uploads.

------------------------------------------------------------------------------

## AbortMultipartUpload
```c++
  Status AbortMultipartUpload(const std::string& bucket_name,
                              const std::string& key,
                              const std::string& upload_id);
```
#### Request Parameters
  * bucket_name — bucket name
  * key — object key
  * upload_id — unique id for upload


------------------------------------------------------------------------------

## ListMultipartUploads
```c++
  Status ListMultipartUploads(const ListMultipartUploadsRequest& request,
                              ListMultipartUploadsResult* result);
```
#### Request Parameters
  * bucket_name — bucket name
  * delimiter — delimiter used to group uploads
  * max-key — return uploads must no more than max-keys.
  * key_marker — keys must start from key_marker.
  * prefix — return objects must begin with prefix
  * upload_id_marker — upload id must start from upload_id_marker.



------------------------------------------------------------------------------

## ListParts
```c++
  Status ListParts(const ListPartsRequest& request, ListPartsResult* result);
```
#### Request Parameters
  * bucket_name — bucket name
  * key — object key
  * upload_id_ —  unique id for upload
  * max-parts — return parts must no more than max-parts
  * part_number_marker — part number must start from part_number_marker
