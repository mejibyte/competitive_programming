# @param {Integer[]} nums1
# @param {Integer[]} nums2
# @return {Integer[]}
def intersection(nums1, nums2)
    seen = {}
    nums1.each do |x|
        seen[x] = true
    end
    nums2.map do |x|
        if seen[x]
            seen.delete(x)
            x
        end
    end.compact
end
