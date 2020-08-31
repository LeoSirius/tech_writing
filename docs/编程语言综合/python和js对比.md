# python和js对比

这两个语言是我作为web开发者用的最多的语言。在学习的过程中为了避免混淆，特此记录两门语言的差别

## 比较运算

python中is判断的是不是同一个对象，==判断的是值是否相等

```python
>>> a = [1,2]
>>> b = [1,2]
>>> a is b      # a和b引用的不是同一个对象，他们的值是相等的
False
>>> a == b
True
```

js中 == 比较的是不是同一个实例。

```js
[1] == [1]    // 这两个数组是两个对象。
false
```

js中要比较两个数字的值是否相等，是没有直接的方法的。这点js比python更接近c。要比较数组的值，可以手动实现一个equals方法

```js
// Warn if overriding existing method
if(Array.prototype.equals)
    console.warn("Overriding existing Array.prototype.equals. Possible causes: New API defines the method, there's a framework conflict or you've got double inclusions in your code.");
// attach the .equals method to Array's prototype to call it on any array
Array.prototype.equals = function (array) {
    // if the other array is a falsy value, return
    if (!array)
        return false;

    // compare lengths - can save a lot of time
    if (this.length != array.length)
        return false;

    for (var i = 0, l=this.length; i < l; i++) {
        // Check if we have nested arrays
        if (this[i] instanceof Array && array[i] instanceof Array) {
            // recurse into the nested arrays
            if (!this[i].equals(array[i]))
                return false;       
        }           
        else if (this[i] != array[i]) { 
            // Warning - two different object instances will never be equal: {x:20} != {x:20}
            return false;   
        }           
    }       
    return true;
}
// Hide method from for-in loops
Object.defineProperty(Array.prototype, "equals", {enumerable: false});


var a = [1];
var b = [1];

a.equals(b);    // true
```

