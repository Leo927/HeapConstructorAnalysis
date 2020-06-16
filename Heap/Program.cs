using System;

namespace Heap
{
    class Program
    {
        static void Main(string[] args)
        {
            Heap heap = new Heap();
            heap.Add(5);
            heap.Add(10);
            heap.Add(20);
            heap.Add(1);
            heap.Add(5, 20, 64, 84, 36, 94, 24, 15, 36);
            var count = heap.Values.Count;
            for (int i = 0; i < count; i++)
            {
                Console.WriteLine(heap.Pop());
            }

        }
    }
}
