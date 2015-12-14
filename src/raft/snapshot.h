/*
 * =====================================================================================
 *
 *       Filename:  snapshot.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015/11/04 14:00:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  WangYao (fisherman), wangyao02@baidu.com
 *        Company:  Baidu, Inc
 *
 * =====================================================================================
 */
#ifndef PUBLIC_RAFT_RAFT_SNAPSHOT_H
#define PUBLIC_RAFT_RAFT_SNAPSHOT_H

#include <string>
#include "raft/storage.h"

namespace raft {

class LocalSnapshotWriter : public SnapshotWriter {
public:
    LocalSnapshotWriter(const std::string& path);
    virtual ~LocalSnapshotWriter();

    int64_t snapshot_index();
    virtual int init();
    virtual int copy(const std::string& uri);
    virtual int save_meta(const SnapshotMeta& meta);
    virtual std::string get_uri(const base::EndPoint& hint_addr);
protected:
    static const char* _s_snapshot_meta;
    std::string _path;
    SnapshotMeta _meta;
};

class LocalSnapshotReader: public SnapshotReader {
public:
    LocalSnapshotReader(const std::string& path);
    virtual ~LocalSnapshotReader();

    virtual int init();
    virtual int load_meta(SnapshotMeta* meta);
    virtual std::string get_uri(const base::EndPoint& hint_addr);
protected:
    static const char* _s_snapshot_meta;
    std::string _path;
};

class LocalSnapshotStorage : public SnapshotStorage {
public:
    LocalSnapshotStorage(const std::string& path);
    virtual ~LocalSnapshotStorage();

    static const char* _s_temp_path;

    virtual int init();
    virtual SnapshotWriter* create();
    virtual int close(SnapshotWriter* writer);

    virtual SnapshotReader* open();
    virtual int close(SnapshotReader* reader);
protected:
    std::string _path;
    int64_t _last_snapshot_index;
};

SnapshotStorage* create_local_snapshot_storage(const std::string& uri);

}

#endif //~PUBLIC_RAFT_RAFT_SNAPSHOT_H