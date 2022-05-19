#include <bits/stdc++.h>
using namespace std;
// A Huffman tree node
struct MinHeapNode
{
    char data;
    unsigned freq;
    MinHeapNode *left, *right;

    MinHeapNode(char data, unsigned freq)
    {

        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

// For comparison of two heap nodes (needed in min heap)
struct compare
{
    bool operator()(MinHeapNode *l, MinHeapNode *r)

    {
        return (l->freq > r->freq);
    }
};

void printCodes(struct MinHeapNode *root, string str,int *count)
{

    *count=*count+1;
    if (!root)
        return;

    if (root->data != '$')
        cout << root->data << ": " << str << "\n";

    printCodes(root->left, str + "0",count);
    printCodes(root->right, str + "1",count);

}

//build huffman tree and print by traversing it
void HuffmanCodes(char data[], int freq[], int size,int *count)
{
    struct MinHeapNode *left, *right, *top;
    priority_queue<MinHeapNode *, vector<MinHeapNode *>, compare> minHeap;
    
    for (int i = 0; i < size; ++i)
    {
        minHeap.push(new MinHeapNode(data[i], freq[i])); // insert arr[] in min heap
        *count=*count+1;
    }
    while (minHeap.size() != 1)
    {
        //extract 2 min element from minheap
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();

        //new internal node with freq=sum of 2 min element extracted before
        top = new MinHeapNode('$', left->freq + right->freq);
        // 2 extracted node as left and right children of this new added node
        //$= special value for internal nodes(sum)
        top->left = left;
        top->right = right;

        minHeap.push(top);
        *count=*count+1;
    }
    printCodes(minHeap.top(), "",count);

}


int main()
{

    char arr[] = {'p','i','e','r','c','k','d','a','o','f','l','s'}; //Piper Picked a Peck Of Pickled Peppers
    int freq[] = {8,3,6,2,3,3,2,1,1,1,1,1};
    
    // int inp=200;
    // char arr[inp];
    // int freq[inp];
    int count=0;
    // for(int i=0;i<inp;i++)
    // {
    //     int r=rand();
    //     arr[i]='a'+r;
    // }

    //     for(int i=0;i<inp;i++)
    // {
    //     freq[i]=rand()%100;
    // }
    int size = sizeof(arr) / sizeof(arr[0]);
    cout<<endl<<endl;

    // for(int i=0;i<size;i++){
    //     cout<<arr[i]<<"  :  "<<freq[i]<<"\n";
    // }
    HuffmanCodes(arr, freq, size,&count);
    // cout<<"Count is: "<<count;
    return 0;
}