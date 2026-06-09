<?php
class Player
{
    public $jersey;
    function set_jersey($j)
    {
        $this->jersey = $j;
    }
    function display()
    {
        echo "Jersey: $this->jersey<br>";
    }
}
class Striker extends Player
{
    public $skill;
    function set_skill($s)
    {
        $this->skill = $s;
    }
    function display()
    {
        Player::display();
        echo "Skill: $this->skill";
    }
}

$ronaldo = new Striker();
$ronaldo->set_jersey(10);
$ronaldo->set_skill("Heading");
$ronaldo->display();
?>