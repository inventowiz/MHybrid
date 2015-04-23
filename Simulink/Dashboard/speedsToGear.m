function [ gear ] = speedsToGear( engine,wheel )
    primary_gear = (24/73);
    gear1=13/32;
    gear2=16/32;
    gear3=17/28;
    gear4=19/26;
    gear5=21/25;
    sprockets=13/50;
    
    output_rpm = wheel;
    engine_rpm = engine;
    
    gear = 0;
    
    %calculates the engine speed for each gear based on the actual output
    engine_rpm1 = output_rpm/(primary_gear * sprockets * gear1);
    engine_rpm2 = output_rpm/(primary_gear * sprockets * gear2);
    engine_rpm3 = output_rpm/(primary_gear * sprockets * gear3);
    engine_rpm4 = output_rpm/(primary_gear * sprockets * gear4);
    engine_rpm5 = output_rpm/(primary_gear * sprockets * gear5);

    if engine_rpm1 <= engine_rpm + engine_rpm * .1 && engine_rpm1 >= engine_rpm - engine_rpm * .1
        gear = 1;
    end
    if engine_rpm2 <= engine_rpm + engine_rpm * .1 && engine_rpm2 >= engine_rpm - engine_rpm * .1
        gear = 2;
    end
    if engine_rpm3 <= engine_rpm + engine_rpm * .1 && engine_rpm3 >= engine_rpm - engine_rpm * .1
        gear = 3;
    end
    if engine_rpm4 <= engine_rpm + engine_rpm * .1 && engine_rpm4 >= engine_rpm - engine_rpm * .1
        gear = 4;
    end
    if engine_rpm5 <= engine_rpm + engine_rpm * .1 && engine_rpm5 >= engine_rpm - engine_rpm * .1
        gear = 5;
    end   
end

