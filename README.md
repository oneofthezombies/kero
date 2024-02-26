# Kero

Kero is an experimental asynchronous JavaScript dialect programming language.  

__Less is better than more.__  

Async should be the default, and Sync should be an option. Because I think Async has been proven to be useful.  

## Features

- All functions implicitly return Promise.  
- All function calls are implicitly await.

## Pros and Cons

### Pros

- This can avoid the "floating promise" problem.  
- Since there is no boilerplate "async/await" syntax, users can focus on business logic.  

### Cons

- Because the basis of this is Async, not Sync, the user must ensure that it is performed "atomically" when accessing and processing shared state.  

![mascot](/resources/mascot.webp)
