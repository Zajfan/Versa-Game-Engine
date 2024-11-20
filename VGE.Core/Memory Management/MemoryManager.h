#pragma once

#include "VGE.Core.h"
#include <vector>
#include <mutex>

namespace VGE {

// Memory block structure
struct MemoryBlock {
    void* address;
    size_t size;
    bool used;
    MemoryBlock* next;
};

class MemoryPool {
public:
    MemoryPool(size_t size);
    ~MemoryPool();

    void* allocate(size_t size, size_t alignment);
    void deallocate(void* ptr);

private:
    void* m_memory;
    size_t m_size;
    MemoryBlock* m_firstBlock;
    std::mutex m_mutex;
};

class MemoryManager : public IMemoryAllocator {
public:
    MemoryManager() = default;
    ~MemoryManager() override = default;

    bool initialize(size_t defaultPoolSize);
    void shutdown();

    // IMemoryAllocator interface
    void* allocate(size_t size, size_t alignment = alignof(std::max_align_t)) override;
    void deallocate(void* ptr) override;

    // Memory statistics
    size_t getTotalAllocated() const;
    size_t getTotalAvailable() const;
    void dumpMemoryStats() const;

private:
    std::unique_ptr<MemoryPool> m_defaultPool;
    std::mutex m_mutex;
    size_t m_totalAllocated{0};
};

} // namespace VGE
