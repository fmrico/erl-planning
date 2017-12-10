(define (problem attending_visitors_task)
(:domain attending_visitors)
(:objects
    l_kitchen l_start l_entrance l_bedroom - location
    Apu Nick - visitor
		Leia - robot
		Annie - host
		Doorbell - bell
)
(:init
    (bedroom_location l_bedroom)
		(entrance_location l_entrance)
		(kitchen_location l_kitchen)
		(start_location l_start)

    (deli_person Apu)
    (doctor_person Nick)

		(robot_at Leia l_start)

		(person_at Apu l_entrance)
		(bell_ringed doorbell)

)
(:goal (and
	(mission_accomplished Leia)
)))
