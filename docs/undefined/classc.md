# ClassC

<pre class="language-mermaid"><code class="lang-mermaid">classDiagram
class GameManager{
    - int id;
    + string name;
    + int getId();
}  

class GameManager2{
    - int id;
    + string name;
    + int getId();
}  
<strong>
</strong>GameManager &#x3C;|-- GameManager2

</code></pre>

