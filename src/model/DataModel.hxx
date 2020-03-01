#ifndef DATA_MODEL_HXX
#define DATA_MODEL_HXX

#include "iModel.hxx"
#include "../util/Observer.hxx"
#include "../engine/MessageQueue.hxx"

template <typename DataArgs>
struct UIMQDispatcher
{
  UILoopMQ & loop;
  void dispatch(ObserverSPtr<DataArgs> observer, typename Observer<DataArgs>::Notification notification)
  {
    loop.push(UIChangeEvent{ observer, std::move(notification) });
  }
};


template <typename DataArgs>
struct DataModel : public iModel, public Subject<DataArgs, UIMQDispatcher<DataArgs>>
{
  DataModel(UILoopMQ & mq) : Subject<DataArgs, UIMQDispatcher<DataArgs>>(UIMQDispatcher<DataArgs>{mq}) { }
};

#endif // DATA_MODEL_HXX
