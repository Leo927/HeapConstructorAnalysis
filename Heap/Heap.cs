using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Markup;

namespace Heap
{
    public class Heap
    {
        private List<StatedValue> values;

        const int root = 1;

        public enum State
        {
            Empty,
            Deleted,
            Occupied
        }

        public class StatedValue
        {
            public State state;
            public IComparable value;
            public StatedValue(IComparable _value)
            {
                this.value = _value;
                state = State.Occupied;
            }
        }
        public List<StatedValue> Values
        {
            get { return values; }
            set { values = value; }
        }

        public Heap()
        {
            values = new List<StatedValue>();
        }

        bool Contains(IComparable value)
        {
            return values.Find(x => x.value.Equals(value) && x.state == State.Occupied) != null;
        }

        public bool Add(IComparable value)
        {
            if (Contains(value) == true)
                return false;
            
            values.Add(new StatedValue(value));

            BubbleUp(values.Count - 1);
            return true;
        }

        public void Add(params IComparable[] _values)
        {
            foreach(var value in _values)
            {
                Add(value);
            }
        }

        private void Print()
        {
            values.ForEach(x => Console.WriteLine(x.value));
        }

        private void BubbleUp(int position)
        {
            if (Parent(position) == null) return;
            var parentValue = GetValue((int)Parent(position));

            if (parentValue.CompareTo(GetValue(position)) > 0)
            {
                SwapStatedValue(position, (int)Parent(position));
                BubbleUp((int)Parent(position));
            }
        }

        private int? Parent(int position)
        {
            if (position == 0) return null;
            return (position - 1) / 2;
        }

        private IComparable GetValue(int position)
        {
            if (position < 0 || position >= values.Count)
                return null;
            return values[position].value;
        }

        private void SwapStatedValue(int lhs, int rhs)
        {
            StatedValue temp = values[lhs];
            values[lhs] = values[rhs];
            values[rhs] = temp;
        }

        public IComparable Pop()
        {
            if (values.Count == 0) return null;

            var result = GetValue(0);
            var insertPos = BubbleDown(0);
            SwapStatedValue(insertPos, values.Count - 1);
            values.RemoveAt(values.Count - 1);
            return result;
        }

        private int BubbleDown(int position)
        {
            var lastValue = GetValue(values.Count - 1);
            if (Invariant(position, lastValue))
                return position;
            var minChild = FindMinChild(position);            
            SwapStatedValue((int)minChild, position);
            return BubbleDown((int)minChild);
        }

        private int? FindMinChild(int position)
        {
            int? minChild =null;
            var children = GetChildren(position);
            if (children.left != null)
                minChild = (int)children.left;
            if (children.right != null)
                if(GetValue((int)children.right).CompareTo(GetValue((int)children.left))<0 
                    || children.left == null)
                {
                    minChild = (int)children.right;
                }
            return minChild;
        }

        private (int? left, int? right) GetChildren(int position)
        {
            int? left = position * 2 + 1;
            int? right = position * 2 + 2;
            
            if (left >= values.Count) left = null;
            if (right >= values.Count) right = null;
            return (left, right);
        }

        private bool Invariant(int position, IComparable value)
        {
            var children = GetChildren(position);
            if (children.left !=null &&
                value.CompareTo(GetValue((int)children.left)) > 0)
                return false;
            if (children.right != null &&
                value.CompareTo(GetValue((int)children.right)) > 0)
                return false;
            return true;
        }


    }
}
