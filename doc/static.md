# Static variables

- Static variables are variables created within a form (a function), and can't be accessed outside the form code block.

```cpp
int StaticTest() public
{
	static[str]statictest="Static works here"
	console.println.log(statictest)
	return 1
}

console.println.log(statictest); // Won't work.
```