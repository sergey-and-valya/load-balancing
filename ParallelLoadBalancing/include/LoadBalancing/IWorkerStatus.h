#ifndef _IWORKERSTATUS_H
#define _IWORKERSTATUS_H

class IWorkerStatus
{
public:
	virtual bool Completed() = 0;
	virtual void Wait() = 0;
};

#endif // _IWORKERSTATUS_H