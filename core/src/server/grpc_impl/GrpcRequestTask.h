// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#pragma once

#include "db/Types.h"
#include "server/grpc_impl/GrpcRequestScheduler.h"
#include "utils/Status.h"

#include "grpc/gen-milvus/milvus.grpc.pb.h"
#include "grpc/gen-status/status.pb.h"

#include <condition_variable>
#include <memory>
#include <string>
#include <vector>

namespace milvus {
namespace server {
namespace grpc {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CreateTableTask : public GrpcBaseTask {
 public:
    static BaseTaskPtr
    Create(const ::milvus::grpc::TableSchema* schema);

 protected:
    explicit CreateTableTask(const ::milvus::grpc::TableSchema* schema);

    Status
    OnExecute() override;

 private:
    const ::milvus::grpc::TableSchema* schema_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class HasTableTask : public GrpcBaseTask {
 public:
    static BaseTaskPtr
    Create(const std::string& table_name, bool& has_table);

 protected:
    HasTableTask(const std::string& table_name, bool& has_table);

    Status
    OnExecute() override;

 private:
    std::string table_name_;
    bool& has_table_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DescribeTableTask : public GrpcBaseTask {
 public:
    static BaseTaskPtr
    Create(const std::string& table_name, ::milvus::grpc::TableSchema* schema);

 protected:
    DescribeTableTask(const std::string& table_name, ::milvus::grpc::TableSchema* schema);

    Status
    OnExecute() override;

 private:
    std::string table_name_;
    ::milvus::grpc::TableSchema* schema_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DropTableTask : public GrpcBaseTask {
 public:
    static BaseTaskPtr
    Create(const std::string& table_name);

 protected:
    explicit DropTableTask(const std::string& table_name);

    Status
    OnExecute() override;

 private:
    std::string table_name_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CreateIndexTask : public GrpcBaseTask {
 public:
    static BaseTaskPtr
    Create(const ::milvus::grpc::IndexParam* index_param);

 protected:
    explicit CreateIndexTask(const ::milvus::grpc::IndexParam* index_param);

    Status
    OnExecute() override;

 private:
    const ::milvus::grpc::IndexParam* index_param_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ShowTablesTask : public GrpcBaseTask {
 public:
    static BaseTaskPtr
    Create(::milvus::grpc::TableNameList* table_name_list);

 protected:
    explicit ShowTablesTask(::milvus::grpc::TableNameList* table_name_list);

    Status
    OnExecute() override;

 private:
    ::milvus::grpc::TableNameList* table_name_list_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class InsertTask : public GrpcBaseTask {
 public:
    static BaseTaskPtr
    Create(const ::milvus::grpc::InsertParam* insert_param, ::milvus::grpc::VectorIds* record_ids);

 protected:
    InsertTask(const ::milvus::grpc::InsertParam* insert_param, ::milvus::grpc::VectorIds* record_ids);

    Status
    OnExecute() override;

 private:
    const ::milvus::grpc::InsertParam* insert_param_;
    ::milvus::grpc::VectorIds* record_ids_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SearchTask : public GrpcBaseTask {
 public:
    static BaseTaskPtr
    Create(const ::milvus::grpc::SearchParam* search_param, const std::vector<std::string>& file_id_array,
           ::milvus::grpc::TopKQueryResult* response);

 protected:
    SearchTask(const ::milvus::grpc::SearchParam* search_param, const std::vector<std::string>& file_id_array,
               ::milvus::grpc::TopKQueryResult* response);

    Status
    OnExecute() override;

 private:
    const ::milvus::grpc::SearchParam* search_param_;
    std::vector<std::string> file_id_array_;
    ::milvus::grpc::TopKQueryResult* topk_result_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CountTableTask : public GrpcBaseTask {
 public:
    static BaseTaskPtr
    Create(const std::string& table_name, int64_t& row_count);

 protected:
    CountTableTask(const std::string& table_name, int64_t& row_count);

    Status
    OnExecute() override;

 private:
    std::string table_name_;
    int64_t& row_count_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CmdTask : public GrpcBaseTask {
 public:
    static BaseTaskPtr
    Create(const std::string& cmd, std::string& result);

 protected:
    CmdTask(const std::string& cmd, std::string& result);

    Status
    OnExecute() override;

 private:
    std::string cmd_;
    std::string& result_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DeleteByRangeTask : public GrpcBaseTask {
 public:
    static BaseTaskPtr
    Create(const ::milvus::grpc::DeleteByRangeParam* delete_by_range_param);

 protected:
    explicit DeleteByRangeTask(const ::milvus::grpc::DeleteByRangeParam* delete_by_range_param);

    Status
    OnExecute() override;

 private:
    const ::milvus::grpc::DeleteByRangeParam* delete_by_range_param_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PreloadTableTask : public GrpcBaseTask {
 public:
    static BaseTaskPtr
    Create(const std::string& table_name);

 protected:
    explicit PreloadTableTask(const std::string& table_name);

    Status
    OnExecute() override;

 private:
    std::string table_name_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DescribeIndexTask : public GrpcBaseTask {
 public:
    static BaseTaskPtr
    Create(const std::string& table_name, ::milvus::grpc::IndexParam* index_param);

 protected:
    DescribeIndexTask(const std::string& table_name, ::milvus::grpc::IndexParam* index_param);

    Status
    OnExecute() override;

 private:
    std::string table_name_;
    ::milvus::grpc::IndexParam* index_param_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DropIndexTask : public GrpcBaseTask {
 public:
    static BaseTaskPtr
    Create(const std::string& table_name);

 protected:
    explicit DropIndexTask(const std::string& table_name);

    Status
    OnExecute() override;

 private:
    std::string table_name_;
};

}  // namespace grpc
}  // namespace server
}  // namespace milvus
