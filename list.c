#include<stdio.h>
#include<stdlib.h>
#if defined(WIN32) && !defined(__cplusplus)
#define inline __inline
#endif

struct list_head {
	struct list_head *next;
	struct list_head *prev;
};


#define INIT_LIST_HEAD(head) do {			\
		(head)->next = (head)->prev = head;	\
	} while (0)


static inline void
list_add (struct list_head *new, struct list_head *head)
{
	new->prev = head;
	new->next = head->next;

	new->prev->next = new;
	new->next->prev = new;
}


static inline void
list_add_tail (struct list_head *new, struct list_head *head)
{
	new->next = head;
	new->prev = head->prev;

	new->prev->next = new;
	new->next->prev = new;
}


static inline void
list_del (struct list_head *old)
{
	old->prev->next = old->next;
	old->next->prev = old->prev;

	old->next = (void *)0xbabebabe;
	old->prev = (void *)0xcafecafe;
}


static inline void
list_del_init (struct list_head *old)
{
	old->prev->next = old->next;
	old->next->prev = old->prev;

	old->next = old;
	old->prev = old;
}


static inline void
list_move (struct list_head *list, struct list_head *head)
{
	list_del (list);
	list_add (list, head);
}


static inline void
list_move_tail (struct list_head *list, struct list_head *head)
{
	list_del (list);
	list_add_tail (list, head);
}


static inline int
list_empty (struct list_head *head)
{
	return (head->next == head);
}


static inline void
__list_splice (struct list_head *list, struct list_head *head)
{
	(list->prev)->next = (head->next);
	(head->next)->prev = (list->prev);

	(head)->next = (list->next);
	(list->next)->prev = (head);
}


static inline void
list_splice (struct list_head *list, struct list_head *head)
{
	if (list_empty (list))
		return;

	__list_splice (list, head);
}


static inline void
list_splice_init (struct list_head *list, struct list_head *head)
{
	if (list_empty (list))
		return;

	__list_splice (list, head);
	INIT_LIST_HEAD (list);
}


#define list_entry(ptr, type, member)					\
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))


#define list_for_each(pos, head)				     \
	for (pos = (head)->next; pos != (head); pos = pos->next)


#define list_for_each_entry(pos, head, member)				\
	for (pos = list_entry((head)->next, typeof(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = list_entry(pos->member.next, typeof(*pos), member))


#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = list_entry((head)->next, typeof(*pos), member),	\
		n = list_entry(pos->member.next, typeof(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = n, n = list_entry(n->member.next, typeof(*n), member))

struct student
{
	int no;
	char *name;
	struct list_head list;
};
struct stulist
{
	struct list_head headnode;
};

int main()
{
	struct stulist *pstulist=(struct stulist *)malloc(sizeof(struct stulist));
	struct student stu1={101,"tank"};
	struct student stu2={102,"litan"};
	struct student *pstu;
	struct list_head *pos;
	INIT_LIST_HEAD(&pstulist->headnode);
	//printf("%d,%s,%p",stu.no,stu.name,stu.list);
	list_add_tail(&stu1.list,&pstulist->headnode);
	list_add_tail(&stu2.list,&pstulist->headnode);

	pos=NULL;
	if(list_empty(&pstulist->headnode))
		printf("no student\n");
	else
	{
		list_for_each(pos,&pstulist->headnode)
		{
			pstu=list_entry(pos,struct student,list);
			printf("%d,%s\n",pstu->no,pstu->name);
		}
	}
	

}
