# Definition for singly-linked list.
# class ListNode
#     attr_accessor :val, :next
#     def initialize(val)
#         @val = val
#         @next = nil
#     end
# end

# @param {ListNode} l1
# @param {ListNode} l2
# @return {ListNode}

# Recursive version
def add_two_numbers(l1, l2, carry = 0)
    if (l1 == nil and l2 == nil)
        return carry > 0 ? ListNode.new(carry) : nil
    end
    sum = (l1&.val || 0) + (l2&.val || 0) + carry
    answer = ListNode.new(sum % 10)
    answer.next = add_two_numbers(l1&.next, l2&.next, sum / 10)
    return answer
end


# Iterative
def add_two_numbers(p, q)
    head = tail = nil
    carry = 0
    while p || q || carry > 0
        sum = (p&.val || 0) + (q&.val || 0) + carry
        if head.nil?
            head = tail = ListNode.new(sum % 10)
        else
            tail.next = ListNode.new(sum % 10)
            tail = tail.next
        end

        carry = sum / 10
        p, q = p&.next, q&.next
    end
    return head
end

