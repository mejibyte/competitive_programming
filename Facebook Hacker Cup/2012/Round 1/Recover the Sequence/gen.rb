def merge(arr1, arr2)
    result = []
    while arr1.size > 0 and arr2.size > 0
        if arr1[0] < arr2[0]
            print '1' # for debugging
            result << arr1.shift
        else
            print '2' # for debugging
            result << arr2.shift
        end
    end
            
    result += arr1
    result += arr2
    return result
end

def merge_sort(arr)
    n = arr.size
    return arr if n <= 1

    mid = n / 2
    
    first_half = merge_sort(arr[0..mid-1])
    second_half = merge_sort(arr[mid..n-1])
    return merge(first_half, second_half)
end


t = 100
puts t
t.times do
  n = rand(10_000 - 1) + 2
  puts n
  array = (1..n).to_a.sample(n)
  sorted = merge_sort(array)
  puts
end