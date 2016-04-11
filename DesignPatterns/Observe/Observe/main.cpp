#include <iostream>
#include "Subject.h"
#include "Observer.h"
#include "ConcreteSubject.h"
#include "Subject.h"
#include "ConCreteObserverA.h"
#include "ConCreteObserverB.h"

using namespace std;
int main() {
// Create Subject
     Subject *pSubject = new ConcreteSubject();

     // Create Observer
     Observer *pObserverA = new ConCreteObserverA(pSubject);
     Observer *pObserverB = new ConCreteObserverB(pSubject);

     // Change the state
     pSubject->SetState(2);

     // Register the observer
     pSubject->Attach(pObserverA);
     pSubject->Attach(pObserverB);

     pSubject->Notify();

     std::cout << "----------------------------------" << std::endl;

     // Unregister the observer
     pSubject->Detach(pObserverA);

     pSubject->SetState(3);
     pSubject->Notify();

     delete pObserverA;
     delete pObserverB;
     delete pSubject;
}
