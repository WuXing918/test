#include <iostream>
#include "Composite.h"
#include "Leaf.h"
#include <iostream>
using namespace std;

int main()
{
    Composite *root = new Composite("root");
    Leaf *leaf1 = new Leaf("leaf1");
    Leaf *leaf2 = new Leaf("leaf2");
    root->AddComponent(leaf1);
    root->AddComponent(leaf2);

    Composite *lay2 = new Composite("layer2");
    Leaf *leaf4 = new Leaf("leaf4");
    lay2->AddComponent(leaf4);

    Composite *lay1 = new Composite("layer1");
    Leaf *leaf3 = new Leaf("leaf3");
    lay1->AddComponent(leaf3);
    lay1->AddComponent(lay2);

    root->AddComponent(lay1);

    root->GetChild(1);
    cout<<endl;
    lay1->GetChild(1);
    cout<<endl;
    lay2->GetChild(1);

    delete root;
    delete lay1;
    delete lay2;
    delete leaf1;
    delete leaf2;
    delete leaf3;
    delete leaf4;
    // system("pause");
    return 0;
}
