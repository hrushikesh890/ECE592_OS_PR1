#define	NSPINLOCKS	20
#define	NLOCKS		20
#define	NALOCKS		20
				
extern	int	num_spinlocks;
extern	int	num_locks;
extern	int	num_active_locks;
extern	void	 sync_printf(char*, ...);
extern	uint32 test_and_set(uint32* , uint32);
pid32	active_lock_list[NALOCKS];
typedef	uint32	sl_lock_t;

typedef struct	lock_t{
bool8	flag;
uint32	guard;
qid16	q_park;
bool8	about_to_park;
}lock_t;

typedef struct	al_lock_t{
bool8	flag;
uint32	guard;
qid16	q_park;
bool8	about_to_park;
int	id;
}al_lock_t;
extern	void sync_printf(char *, ...);
extern 	syscall	sl_initlock(sl_lock_t*);
extern	syscall sl_lock(sl_lock_t*);
extern	syscall	sl_unlock(sl_lock_t*);

extern	syscall	initlock(lock_t*);
extern	syscall	lock(lock_t*);
extern	syscall	unlock(lock_t*);
extern	void	set_park(lock_t*);
extern 	void	park(lock_t*);
extern 	void	unpark(lock_t*, pid32);

extern	syscall	al_initlock(al_lock_t*);
extern	syscall	al_lock(al_lock_t*);
extern	syscall	al_unlock(al_lock_t*);
extern	void	al_set_park(al_lock_t*);
extern 	void	al_park(al_lock_t*);
extern 	void	al_unpark(al_lock_t*, pid32);
extern	bool8	al_trylock(al_lock_t*);
