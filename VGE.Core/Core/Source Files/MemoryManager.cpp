#include "../Header Files/MemoryManager.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>

namespace VGE {

// Helper functions
static size_t alignForward(size_t addr, size_t alignment) {
    return (addr + (alignment - 1)) & ~(alignment - 1);
}

// MemoryPool implementation
MemoryPool::MemoryPool(size_t size) : m_size(size) {
    m_memory = std::malloc(size);
    if (!m_memory) {
        throw std::runtime_error("Failed to allocate memory pool");
    }

    m_firstBlock = new MemoryBlock{
        m_memory,
        size,
        false,
        nullptr
    };
}

MemoryPool::~MemoryPool() {
    std::free(m_memory);
    delete m_firstBlock;
}

void* MemoryPool::allocate(size_t size, size_t alignment) {
    std::lock_guard<std::mutex> lock(m_mutex);

    MemoryBlock* block = m_firstBlock;
    MemoryBlock* prev = nullptr;

    while (block) {
        if (!block->used) {
            size_t alignedAddr = alignForward(reinterpret_cast<size_t>(block->address), alignment);
            size_t adjustment = alignedAddr - reinterpret_cast<size_t>(block->address);
            size_t totalSize = size + adjustment;

            if (block->size >= totalSize) {
                // Split block if there's enough space
                if (block->size >= totalSize + sizeof(MemoryBlock) + 32) {
                    MemoryBlock* newBlock = new MemoryBlock{
                        reinterpret_cast<void*>(reinterpret_cast<char*>(block->address) + totalSize),
                        block->size - totalSize,
                        false,
                        block->next
                    };

                    block->size = totalSize;
                    block->next = newBlock;
                }

                block->used = true;
                return reinterpret_cast<void*>(alignedAddr);
            }
        }

        prev = block;
        block = block->next;
    }

    return nullptr;
}

void MemoryPool::deallocate(void* ptr) {
    if (!ptr) return;

    std::lock_guard<std::mutex> lock(m_mutex);

    MemoryBlock* block = m_firstBlock;
    MemoryBlock* prev = nullptr;

    while (block) {
        if (block->address <= ptr && 
            reinterpret_cast<char*>(block->address) + block->size > ptr) {
            block->used = false;

            // Merge with next block if it's free
            if (block->next && !block->next->used) {
                block->size += block->next->size;
                MemoryBlock* temp = block->next;
                block->next = temp->next;
                delete temp;
            }

            // Merge with previous block if it's free
            if (prev && !prev->used) {
                prev->size += block->size;
                prev->next = block->next;
                delete block;
            }

            return;
        }

        prev = block;
        block = block->next;
    }
}

// MemoryManager implementation
bool MemoryManager::initialize(size_t defaultPoolSize) {
    try {
        m_defaultPool = std::make_unique<MemoryPool>(defaultPoolSize);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Failed to initialize memory manager: " << e.what() << std::endl;
        return false;
    }
}

void MemoryManager::shutdown() {
    m_defaultPool.reset();
    m_totalAllocated = 0;
}

void* MemoryManager::allocate(size_t size, size_t alignment) {
    std::lock_guard<std::mutex> lock(m_mutex);
    
    void* ptr = m_defaultPool->allocate(size, alignment);
    if (ptr) {
        m_totalAllocated += size;
    }
    return ptr;
}

void MemoryManager::deallocate(void* ptr) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_defaultPool->deallocate(ptr);
}

size_t MemoryManager::getTotalAllocated() const {
    return m_totalAllocated;
}

size_t MemoryManager::getTotalAvailable() const {
    // TODO: Implement actual available memory calculation
    return 0;
}

void MemoryManager::dumpMemoryStats() const {
    std::cout << "Memory Manager Statistics:\n"
              << "Total Allocated: " << m_totalAllocated << " bytes\n"
              << "Total Available: " << getTotalAvailable() << " bytes\n";
}

} // namespace VGE
