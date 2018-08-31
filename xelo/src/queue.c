/*

 * queue.c
 *
 *  Created on: Nov 14, 2017
 *      Author: ThangNguyen

#include "queue.h"
typedef struct Queue {
	int Front, Rear;
	int max_item;
	item Data;
	int count;

} Queue;
Queue queue_message;
void Queue_Init(Queue Q) {
	queue_message.Front = 0;
	queue_message.Rear = -1;
	queue_message.max_item = 10;
	queue_message.count = 0;

}
int IsEmpty(Queue Q) {
	if (Q.count == 0)
		return 1;
	else
		return 0;
}
int IsFull(Queue Q) {
	if (Q.count == Q.max_item)
		return 1;
	else
		return 0;
}
void Push_Circular(Queue Q, item x) {
	if (IsFull(Q)) {
		xprintf("queue full!!! ");
	} else {
		Q.Data[(++Q.Rear) % Q.max_item] = x;
		Q.count++;
	}
}
int Pop_Circular(Queue Q) {
	if (Isempty(Q))
		xprintf("queue empty!!!");
	item x = Q.Data[Q.Front];
	Q.Front = (Q.Front++) % Max;
	Q.count--;
	return x;
}
*/
