/*
 * Memory Manager Assignment
 * Computer Science XII - Computer Systems
 * 
 * This program implements a dynamic game inventory system to practice
 * manual memory management using malloc, calloc, realloc, and free.
 * 
 * You'll experience memory leaks and dangling pointers firsthand,
 * then systematically fix each error.
 */

#include <stdio.h>
#include <stdlib.h>

// =============================================================================
// PART 1: CREATE INVENTORY
// =============================================================================
// Build a basic inventory system that stores item IDs and quantities.
// Use malloc to allocate memory for arrays that will hold this data.

void create_inventory() {
    printf("\n=== PART 1: CREATE INVENTORY ===\n");
    
    int inventory_size = 5;
    int *item_ids = NULL;
    int *quantities = NULL;
    
    // Allocate memory
    item_ids = (int*)malloc(inventory_size * sizeof(int));
    if (item_ids == NULL) {
        printf("Failed to allocate item_ids\n");
        return;
    }

    quantities = (int*)malloc(inventory_size * sizeof(int));
    if (quantities == NULL) {
        printf("Failed to allocate quantities\n");
        free(item_ids);
        return;
    }

    // Fill inventory
    printf("Starting inventory:\n");
    for (int i = 0; i < inventory_size; i++) {
        item_ids[i] = 100 + i;
        quantities[i] = (i + 1) * 10;
        printf("  Item %d: quantity %d\n", item_ids[i], quantities[i]);
    }

    // Free memory
    free(item_ids);
    free(quantities);

    printf("Memory freed successfully.\n");
}

// =============================================================================
// PART 2: EXPAND INVENTORY
// =============================================================================
// Demonstrate dynamic growth using realloc when the player acquires more items
// than the initial inventory can hold.

void expand_inventory() {
    printf("\n=== PART 2: EXPAND INVENTORY ===\n");
    
    int initial_size = 3;
    int expanded_size = 6;
    int *item_ids = NULL;
    int *quantities = NULL;
    
    // Allocate initial memory
    item_ids = (int*)malloc(initial_size * sizeof(int));
    if (item_ids == NULL) {
        printf("Failed to allocate item_ids\n");
        return;
    }

    quantities = (int*)malloc(initial_size * sizeof(int));
    if (quantities == NULL) {
        printf("Failed to allocate quantities\n");
        free(item_ids);
        return;
    }

    // Fill initial inventory
    printf("Initial inventory:\n");
    for (int i = 0; i < initial_size; i++) {
        item_ids[i] = 200 + i;
        quantities[i] = 5 * (i + 1);
        printf("  Item %d: quantity %d\n", item_ids[i], quantities[i]);
    }

    printf("\nExpanding inventory...\n");

    // Reallocate memory
    item_ids = (int*)realloc(item_ids, expanded_size * sizeof(int));
    if (item_ids == NULL) {
        printf("Realloc failed for item_ids\n");
        return;
    }

    quantities = (int*)realloc(quantities, expanded_size * sizeof(int));
    if (quantities == NULL) {
        printf("Realloc failed for quantities\n");
        return;
    }

    // Add new items
    for (int i = initial_size; i < expanded_size; i++) {
        item_ids[i] = 200 + i;
        quantities[i] = 5 * (i + 1);
    }

    // Print expanded inventory
    printf("Expanded inventory:\n");
    for (int i = 0; i < expanded_size; i++) {
        printf("  Item %d: quantity %d\n", item_ids[i], quantities[i]);
    }

    // Free memory
    free(item_ids);
    free(quantities);

    printf("Memory freed successfully.\n");
}

// =============================================================================
// PART 3: MEMORY LEAK DEMONSTRATION
// =============================================================================
// This function demonstrates a memory leak by allocating memory without freeing it.
// Run this version first to see what happens when memory is never freed.

void memory_leak_demo() {
    printf("\n=== PART 3A: MEMORY LEAK DEMO ===\n");
    
    for (int i = 0; i < 1000; i++) {
        int *temp_item = (int*)malloc(1000 * sizeof(int));
        if (temp_item == NULL) return;

        temp_item[0] = i;
        // NO FREE → leak
    }

    printf("Memory leaked!\n");
}

// =============================================================================
// PART 3B: FIXED VERSION - NO MEMORY LEAK
// =============================================================================
// This function properly frees memory after each allocation.
// Compare the behavior of this version to the leaking version above.

void memory_leak_fixed() {
    printf("\n=== PART 3B: FIXED VERSION ===\n");
    
    for (int i = 0; i < 1000; i++) {
        int *temp_item = (int*)malloc(1000 * sizeof(int));
        if (temp_item == NULL) return;

        temp_item[0] = i;

        // FIX
        free(temp_item);
    }

    printf("Memory properly freed.\n");
}

// =============================================================================
// PART 4: SAFE POINTER HANDLING
// =============================================================================
// This function demonstrates dangling pointer issues and how to handle
// pointers safely after freeing memory.

void safe_pointer_handling() {
    printf("\n=== PART 4: SAFE POINTER HANDLING ===\n");
    
    int *player_health = (int*)malloc(sizeof(int));
    if (player_health == NULL) return;

    *player_health = 100;
    printf("Player health: %d\n", *player_health);

    free(player_health);

    // Prevent dangling pointer
    player_health = NULL;

    if (player_health != NULL) {
        printf("Player health: %d\n", *player_health);
    } else {
        printf("Health data not available\n");
    }
}

// =============================================================================
// MAIN FUNCTION
// =============================================================================

int main() {
    printf("MEMORY MANAGER PROGRAM\n");

    create_inventory();
    expand_inventory();
    memory_leak_demo();
    memory_leak_fixed();
    safe_pointer_handling();

    return 0;
}