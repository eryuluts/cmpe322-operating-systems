typedef int BufferItem;
#define BUFFER_SIZE 10;

/*
 * Initialize buffer, mutual exclusion lock and semaphores for empty and
 * full slots.
 */
int InitBuffer();

/*
 * Insert an item into buffer.
 * return 0 on success, -1 on error.
 */
int InsertItem(BufferItem buffer_item);


/*
 * @item: Pointer to BufferItem object.
 * Remove an item from buffer and place it on item.
 * return 0 on success, -1 on error.
 */
int RemoveItem(BufferItem *pbuffer_item);
